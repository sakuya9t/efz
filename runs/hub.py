"""Released agents on Hugging Face (https://huggingface.co/sakuya9t/efz): agent files
(.efzagent, docs/agents.md) and nothing else, one per released build, at the top of the
Hub's repository, with its model card (runs/hub-card.md, the Hub's README.md) beside them.

    python runs/hub.py list                                   # the files there
    python runs/hub.py download                               # every file, into agents/
    python runs/hub.py download agent-league20-spar-s1-round20 --out tmp
    python runs/hub.py upload tmp/NAME.efzagent ... --names ~/data/efz-replays/player_names.csv
    python runs/hub.py card                                   # the card alone, after editing it
    python runs/hub.py remove NAME ...                        # (the Hub's history keeps it)

upload and remove need a login (hf auth login). upload sends agent files only (known by
their header, not their name) and the card, in one commit. It refuses a file that holds
a home folder's path or this machine's login name, and, given --names (a CSV of the
community's player names), one that holds a player's name. The card's table of files is
written by hand: edit it in the same change as the files that go up or come down.

Until 20 November 2026 the Hub held the runs' Stable-Baselines3 checkpoints instead
(runs/<run>/*.zip and their config.json, rounds 1-12 of runs/human-ayu, 3.1 GB). They
were taken down then; the Hub's history keeps them (revision f0dbd7b7), and so does the
Linux machine (~/data/efz-hub-old, the same layout).

Needs huggingface_hub.
"""

import argparse
import csv
import getpass
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
HUB = 'sakuya9t/efz'
CARD = os.path.join(HERE, 'hub-card.md')
SUFFIX = '.efzagent'
MAGIC = b'EFZAGENT'  # (python/efz_env/export.py's)
# A home folder's path, as Linux, Windows and macOS write it.
HOMES = [b'/home/', b'\\users\\', b'/users/']
# Words the exporter writes in a header itself (press_kinds' 'none: jump'), which a
# player's name can be too.
WORDS = {'none'}


def _names(path, allow=()):
    """The player names of a CSV: every cell of 3 bytes or more that isn't a number, one
    of the header's words or a word allowed."""
    with open(os.path.expanduser(path), encoding='utf-8', errors='replace') as f:
        rows = list(csv.reader(f))
    skip = ({c.strip().lower() for c in rows[0]} if rows else set()) | WORDS | {
        a.lower() for a in allow}
    return {c.strip().encode() for r in rows for c in r
            if len(c.strip().encode()) >= 3 and c.strip().lower() not in skip
            and not re.fullmatch(r'[-+0-9.eE]+', c.strip())}


def check(path, names=()):
    """Why this file can't go up ('' if it can)."""
    with open(path, 'rb') as f:
        data = f.read()
    if not path.endswith(SUFFIX) or data[:8] != MAGIC:
        return 'not an agent file' if data[:8] != MAGIC else f'not named {SUFFIX}'
    (size,) = struct.unpack_from('<I', data, 12)
    text = data[16:16 + size]  # the header's keys
    low = data.lower()
    found = [h.decode() for h in HOMES if h in low]
    login = getpass.getuser().lower().encode()
    if len(login) >= 4 and login in low:
        found.append('the login name')
    # A short name only as a whole word of the header (in the tensors it matches numbers
    # by chance); a longer one anywhere.
    hit = sorted(n.decode(errors='replace') for n in names if (
        re.search(rb'(?<![A-Za-z0-9_])' + re.escape(n) + rb'(?![A-Za-z0-9_])', text)
        if len(n) <= 4 else n in data))
    if hit:
        found.append(f'{len(hit)} player name(s): {", ".join(hit[:5])}')
    return ', '.join(found)


def _hub_files(api, repo):
    return sorted(f for f in api.list_repo_files(repo) if f.endswith(SUFFIX))


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    p.add_argument('action', choices=('list', 'download', 'upload', 'card', 'remove'))
    p.add_argument('files', nargs='*', help='download/remove: names on the Hub (default: '
                   'all, for download); upload: agent files here')
    p.add_argument('--repo', default=HUB)
    p.add_argument('--out', default=os.path.join(REPO, 'agents'),
                   help='download: the folder (default: agents/)')
    p.add_argument('--names', help="upload: a CSV of player names that mustn't be in a file")
    p.add_argument('--allow', action='append', default=[],
                   help="upload: a name of --names that is an ordinary word of the file's "
                   "header (seen there, not a player's); repeatable")
    p.add_argument('--card', default=CARD, help='the model card (default: runs/hub-card.md)')
    p.add_argument('--message', default=None)
    args = p.parse_args()
    from huggingface_hub import CommitOperationAdd, CommitOperationDelete, HfApi, hf_hub_download
    api = HfApi()
    on_hub = _hub_files(api, args.repo)
    wanted = [n if n.endswith(SUFFIX) else n + SUFFIX for n in args.files]

    if args.action == 'list':
        sizes = {f.path: f.size for f in api.list_repo_tree(args.repo) if hasattr(f, 'size')}
        for n in on_hub:
            print(f'{sizes.get(n, 0) / 1e6:6.1f} MB  {n}')
        return
    if args.action == 'download':
        names = wanted or on_hub
        missing = [n for n in names if n not in on_hub]
        if missing:
            sys.exit(f'not on the Hub: {", ".join(missing)} (python runs/hub.py list)')
        for n in names:
            print(hf_hub_download(args.repo, n, local_dir=args.out))
        return
    if args.action == 'remove':
        missing = [n for n in wanted if n not in on_hub]
        if not wanted or missing:
            p.error(f'remove: name files on the Hub ({", ".join(missing) or "none named"})')
        ops = [CommitOperationDelete(path_in_repo=n) for n in wanted]
        message = args.message or f'Take down {", ".join(wanted)}'
    else:
        if args.action == 'upload' and not args.files:
            p.error('upload: name the agent files')
        if args.action == 'card' and args.files:
            p.error('card: sends the card alone (upload sends files with it)')
        names = _names(args.names, args.allow) if args.names else ()
        bad = {f: check(f, names) for f in args.files}
        bad = {f: why for f, why in bad.items() if why}
        for f, why in bad.items():
            print(f'{f}: {why}', file=sys.stderr)
        if bad:
            sys.exit('nothing sent')
        ops = [CommitOperationAdd(path_in_repo=os.path.basename(f), path_or_fileobj=f)
               for f in args.files]
        message = args.message or (', '.join(os.path.basename(f) for f in args.files)
                                    or 'The model card')
    if os.path.isfile(args.card):  # (the card goes with every change: its table is of the files)
        ops.append(CommitOperationAdd(path_in_repo='README.md', path_or_fileobj=args.card))
    info = api.create_commit(args.repo, ops, commit_message=message)
    print(info.commit_url)


if __name__ == '__main__':
    main()
