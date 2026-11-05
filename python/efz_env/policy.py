"""A Stable-Baselines3 policy for EFZ's observations, and a pull toward a reference
policy (people's play, cloned) while it learns by reinforcement.

    from efz_env.policy import EfzPolicy, policy_kwargs
    model = PPO(EfzPolicy, venv, policy_kwargs=policy_kwargs(history=96))

EfzFeatures reads the observation (efz_env's 168 features, then any appended: the input
history of efz_env.history) as a network should take it:

- the actions players are in (self_action, opp_action) are names, not quantities: each
  is embedded, once as the action number (the common ones, below 200, mean the same for
  every character) and once as the character's own (its moves);
- the characters are embedded too;
- the rest is scaled by a mean and a spread (buffers, set from data with set_scale);
- the match's frame count (its scale depends on max_frames) and the CPU flags (people
  never play with one, and the policy shouldn't play differently against it) are left
  out.

EfzPolicy is ActorCriticPolicy with that extractor (one for the actor, one for the
critic), plus set_prior(policy, coef): from then on its training adds coef * KL(it ||
prior) to PPO's loss, so that what it learns by reward stays close to how the prior
plays (KL-regularised RL, as in human-regularised self-play). SB3's PPO has an entropy
bonus and no such term, so it goes in through the entropy evaluate_actions returns:
entropy - (coef / ent_coef) * KL, whose ent_coef-weighted loss is the entropy bonus
plus coef * KL. ent_coef must not be 0. The prior isn't saved with the policy.
"""

import numpy as np
import torch as th
from gymnasium import spaces
from stable_baselines3.common.policies import ActorCriticPolicy
from stable_baselines3.common.torch_layers import BaseFeaturesExtractor

OBS_DIM = 168
SELF_ACTION, OPP_ACTION = 18, 50
SELF_CHAR, OPP_CHAR = 34, 66
DROPPED = (0, 36, 68)  # frame, self_cpu, opp_cpu
ACTIONS = 1024  # action numbers are kept below this
CHARACTERS = 25


def continuous_columns(dim):
    skip = set(DROPPED) | {SELF_ACTION, OPP_ACTION, SELF_CHAR, OPP_CHAR}
    return [i for i in range(dim) if i not in skip]


class EfzFeatures(BaseFeaturesExtractor):
    def __init__(self, observation_space: spaces.Box, action_embed=24, char_embed=8):
        dim = observation_space.shape[0]
        if dim < OBS_DIM:
            raise ValueError(f'expected efz_env observations ({OBS_DIM} features or more)')
        cont = continuous_columns(dim)
        super().__init__(observation_space, len(cont) + 4 * action_embed + 2 * char_embed)
        self.register_buffer('cont', th.tensor(cont, dtype=th.long), persistent=False)
        self.register_buffer('mean', th.zeros(len(cont)))
        self.register_buffer('scale', th.ones(len(cont)))
        self.action = th.nn.Embedding(ACTIONS, action_embed)
        self.own_action = th.nn.Embedding(CHARACTERS * ACTIONS, action_embed)
        self.char = th.nn.Embedding(CHARACTERS, char_embed)

    def set_scale(self, mean, std):
        """The continuous features' mean and spread (over the full observation's
        columns, as numpy arrays of its width, or of the continuous columns')."""
        mean, std = np.asarray(mean, np.float32), np.asarray(std, np.float32)
        idx = self.cont.cpu().numpy()
        if len(mean) != len(idx):
            mean, std = mean[idx], std[idx]
        self.mean.copy_(th.as_tensor(mean))
        self.scale.copy_(th.as_tensor(1.0 / np.maximum(std, 1e-3)))

    def forward(self, obs):
        x = ((obs[:, self.cont] - self.mean) * self.scale).clamp(-10, 10)
        parts = [x]
        for a, c in ((SELF_ACTION, SELF_CHAR), (OPP_ACTION, OPP_CHAR)):
            act = obs[:, a].round().long().clamp(0, ACTIONS - 1)
            char = obs[:, c].round().long().clamp(0, CHARACTERS - 1)
            parts += [self.action(act), self.own_action(char * ACTIONS + act)]
        parts += [self.char(obs[:, SELF_CHAR].round().long().clamp(0, CHARACTERS - 1)),
                  self.char(obs[:, OPP_CHAR].round().long().clamp(0, CHARACTERS - 1))]
        return th.cat(parts, dim=1)


def policy_kwargs(width=512, depth=2):
    return dict(features_extractor_class=EfzFeatures, share_features_extractor=False,
                net_arch=dict(pi=[width] * depth, vf=[width] * depth),
                activation_fn=th.nn.ReLU, ortho_init=False)


class EfzPolicy(ActorCriticPolicy):
    def set_scale(self, mean, std):
        for extractor in (self.pi_features_extractor, self.vf_features_extractor):
            extractor.set_scale(mean, std)

    def set_prior(self, prior, coef, ent_coef):
        """Pulls training toward `prior` (a policy over the same observations, frozen
        here) by coef * KL(self || prior); ent_coef is PPO's."""
        if ent_coef <= 0:
            raise ValueError('the KL goes in through the entropy term: ent_coef > 0')
        prior.set_training_mode(False)
        for p in prior.parameters():
            p.requires_grad_(False)
        # Kept out of the modules: neither trained, nor saved with this policy.
        self.__dict__['prior'] = prior
        self.__dict__['prior_scale'] = coef / ent_coef
        self.__dict__['prior_kl'] = float('nan')

    @property
    def prior_kl(self):
        """The mean KL to the prior over the last batch trained on."""
        return self.__dict__.get('prior_kl', float('nan'))

    def logits(self, obs):
        """The actor's log-probabilities of every action, (batch, actions)."""
        features = self.pi_features_extractor(obs) if not self.share_features_extractor \
            else self.extract_features(obs)
        latent = self.mlp_extractor.forward_actor(features)
        return th.log_softmax(self.action_net(latent), dim=-1)

    def evaluate_actions(self, obs, actions):
        prior = self.__dict__.get('prior')
        if prior is None:
            return super().evaluate_actions(obs, actions)
        # ActorCriticPolicy.evaluate_actions, keeping the distribution's log-probabilities.
        features = self.extract_features(obs)
        if self.share_features_extractor:
            latent_pi, latent_vf = self.mlp_extractor(features)
        else:
            latent_pi = self.mlp_extractor.forward_actor(features[0])
            latent_vf = self.mlp_extractor.forward_critic(features[1])
        distribution = self._get_action_dist_from_latent(latent_pi)
        log_prob = distribution.log_prob(actions)
        values = self.value_net(latent_vf)
        entropy = distribution.entropy()
        logp = distribution.distribution.logits  # normalised: log-probabilities
        with th.no_grad():
            prior_logp = prior.logits(obs)
        kl = (logp.exp() * (logp - prior_logp)).sum(-1)
        self.__dict__['prior_kl'] = float(kl.mean().detach())
        return values, log_prob, entropy - self.__dict__['prior_scale'] * kl
