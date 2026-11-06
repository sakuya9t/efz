"""A language model that reads the game as text (statetext.py) and picks an action.

LLMPolicy is a pretrained causal LM's body (its transformer, without the vocabulary
head) and a head over the 45 actions, read at the prompt's last token. The head starts
as the LM's own output embeddings of the actions' names (' 2A': the mean of its tokens'),
so at the start it is the LM's next-token choice restricted to the action names, and one
forward pass gives the 45 logits (no decoding).

    policy = LLMPolicy.pretrained('HuggingFaceTB/SmolLM2-135M')   # train.py
    policy.save('runs/llm-ayu/smollm')                           # body/, head.pt, llm.json
    agent = LLMAgent('runs/llm-ayu/smollm')                       # plays as efz_env.agent.Agent

LLMAgent plays as efz_env.agent.Agent does (batch, reset, controls, observe), so
runs/human-ayu/evaluate.py plays it (a folder with llm.json): it sees the game `delay`
steps late (its llm.json), its inputs at once, and decides every frame_skip steps.
"""

import json
import os

import numpy as np
import torch as th

import statetext as st

TABLE = st.TABLE


def device_default():
    return 'cuda' if th.cuda.is_available() else 'cpu'


class LLMPolicy(th.nn.Module):
    def __init__(self, body, head, tokenizer):
        super().__init__()
        self.body, self.head, self.tokenizer = body, head, tokenizer

    @classmethod
    def pretrained(cls, base, dtype=None):
        from transformers import AutoModelForCausalLM, AutoTokenizer
        tok = AutoTokenizer.from_pretrained(base)
        lm = AutoModelForCausalLM.from_pretrained(base, dtype=dtype or th.float32)
        body = lm.model if hasattr(lm, 'model') else lm.get_decoder()
        emb = lm.get_output_embeddings().weight.detach().float()
        head = th.nn.Linear(emb.shape[1], len(st.ACTIONS))
        with th.no_grad():
            for i, name in enumerate(st.ACTIONS):
                ids = tok(' ' + name, add_special_tokens=False).input_ids
                head.weight[i] = emb[ids].mean(0)
            head.bias.zero_()
        return cls(body, head, _padded(tok))

    @classmethod
    def load(cls, path, dtype=None, device=None):
        from transformers import AutoModel, AutoTokenizer
        tok = AutoTokenizer.from_pretrained(os.path.join(path, 'body'))
        body = AutoModel.from_pretrained(os.path.join(path, 'body'), dtype=dtype or th.float32)
        hidden = body.config.hidden_size
        head = th.nn.Linear(hidden, len(st.ACTIONS))
        head.load_state_dict(th.load(os.path.join(path, 'head.pt'), map_location='cpu'))
        out = cls(body, head, _padded(tok))
        return out.to(device or device_default())

    def save(self, path, config):
        os.makedirs(path, exist_ok=True)
        body = self.body
        if hasattr(body, 'merge_and_unload'):  # LoRA: the merged weights
            body = body.merge_and_unload()
        body.save_pretrained(os.path.join(path, 'body'))
        self.tokenizer.save_pretrained(os.path.join(path, 'body'))
        th.save(self.head.state_dict(), os.path.join(path, 'head.pt'))
        with open(os.path.join(path, 'llm.json'), 'w') as f:
            json.dump(config, f, indent=1)

    def encode(self, texts, max_len=320):
        device = self.head.weight.device
        b = self.tokenizer(texts, padding=True, truncation=True, max_length=max_len,
                           return_tensors='pt')
        return b['input_ids'].to(device), b['attention_mask'].to(device)

    def forward(self, input_ids, attention_mask):
        """Logits over the 45 actions (float32), from the last token of each prompt."""
        h = self.body(input_ids=input_ids, attention_mask=attention_mask).last_hidden_state
        last = attention_mask.sum(1) - 1  # right padding
        x = h[th.arange(len(h), device=h.device), last]
        return self.head(x.float())


def _padded(tok):
    if tok.pad_token is None:
        tok.pad_token = tok.eos_token
    tok.padding_side = 'right'
    return tok


class LLMAgent:
    """An LLMPolicy playing, as efz_env.agent.Agent does."""

    def __init__(self, path, n=1, deterministic=False, frame_skip=1, player='?', device=None,
                 dtype=None, chunk=128):
        with open(os.path.join(path, 'llm.json')) as f:
            self.config = json.load(f)
        if self.config.get('format') != st.FORMAT:
            raise ValueError(f"{path}: prompts of {self.config.get('format')}, not {st.FORMAT} "
                             '(statetext.py): retrain it')
        self.device = device or device_default()
        if dtype is None:
            dtype = th.bfloat16 if self.device == 'cuda' else th.float32
        self.policy = LLMPolicy.load(path, dtype=dtype, device=self.device).eval()
        self.delay = int(self.config.get('delay', 0))
        self.history = 0  # (its own inputs are in the prompt: no feature history)
        self.frame_skip = frame_skip
        self.deterministic = deterministic
        self.player = str(player)
        self.chunk = chunk
        self.max_len = int(self.config.get('max_len', 320))
        self.rng = np.random.default_rng(0)
        self.batch(n)

    def batch(self, n):
        from efz_env.history import Delay
        self.n = n
        self.seen = Delay((n,), self.delay, 168) if self.delay else None
        self.ctx = st.Context(n, self.config.get('moves', 4), self.config.get('history', 16))
        self.last = None

    def reset(self, mask=None):
        if self.seen is not None:
            self.seen.clear(mask)
        self.ctx.clear(mask)
        if mask is None:
            self.last = None

    @th.no_grad()
    def decide(self, views):
        texts = self.ctx.prompts(views, self.player)
        out = []
        for i in range(0, len(texts), self.chunk):
            ids, mask = self.policy.encode(texts[i:i + self.chunk], self.max_len)
            logits = self.policy(ids, mask)
            if self.deterministic:
                out.append(logits.argmax(1).cpu().numpy())
            else:
                p = th.softmax(logits, 1).cpu().numpy().astype(np.float64)
                p /= p.sum(1, keepdims=True)
                out.append(np.array([self.rng.choice(len(row), p=row) for row in p]))
        return np.concatenate(out)

    def controls(self, obs, step):
        obs = np.asarray(obs, np.float32)[:, :168]
        views = self.seen.push(obs) if self.seen is not None else obs
        self.ctx.view(views)
        if self.last is None or len(self.last) != len(obs) or step % self.frame_skip == 0:
            self.last = self.decide(views)
        return TABLE.to_bytes(self.last)

    def observe(self, controls):
        self.ctx.played(np.asarray(controls, np.uint8))
