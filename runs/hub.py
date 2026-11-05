"""The trained models live on Hugging Face (https://huggingface.co/sakuya9t/efz), under the
same paths as here: runs/<run>/<model>.zip with the settings beside it that
efz_env.agent and the run's scripts read (config.json, <model>.config.json).

    python runs/hub.py download                      # every run's models, into runs/
    python runs/hub.py download human-ayu            # one run's
    python runs/hub.py upload human-ayu              # needs a login: hf auth login
    python runs/hub.py upload human-ayu --exclude 'team/*'

Needs huggingface_hub. upload sends the run's .zip models and settings (the logs and
evaluations stay in the repository, with the scripts).
"""

import argparse
import os

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
HUB = 'sakuya9t/efz'
MODELS = ['*.zip', '**/*.zip', 'config.json', '**/config.json', '*.config.json',
          '**/*.config.json']


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('action', choices=('download', 'upload'))
    p.add_argument('runs', nargs='*', help='folders of runs/ (default: all, for download)')
    p.add_argument('--repo', default=HUB)
    p.add_argument('--exclude', nargs='*', default=[], help='patterns within a run to leave out')
    p.add_argument('--message', default=None)
    args = p.parse_args()
    from huggingface_hub import HfApi, snapshot_download
    if args.action == 'download':
        patterns = [f'runs/{r}/**' for r in args.runs] if args.runs else ['runs/**']
        path = snapshot_download(args.repo, allow_patterns=patterns, local_dir=REPO)
        print('downloaded into', path)
        return
    if not args.runs:
        p.error('upload: name the runs (folders of runs/)')
    api = HfApi()
    for run in args.runs:
        folder = os.path.join(HERE, run)
        info = api.upload_folder(repo_id=args.repo, folder_path=folder,
                                 path_in_repo=f'runs/{run}', allow_patterns=MODELS,
                                 ignore_patterns=args.exclude,
                                 commit_message=args.message or f'runs/{run}: models')
        print(f'runs/{run} ->', info.commit_url if hasattr(info, 'commit_url') else info)


if __name__ == '__main__':
    main()
