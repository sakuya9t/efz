# Naming notes, 31 October 2026

The research behind the names the source got on 31 October 2026 (see
[../readability.md](../readability.md)): eight analyses, one per part of the game, each
reading every use of the unknown members, methods and numbers of its classes. They hold
what didn't fit in a name or a comment: each character's move list (input, command,
action, what it does), its mechanics, the CPU routine's defects, dead content, and bugs
of the original.

They were written against the source **before** the renames, so they use the old names
(`unk118`, `Unk767f60`, `pattern 0xa7`) and that version's line numbers. `renames.txt`
maps each old member and method name to its new one (`CPlayer::unk118 m_rfGauge`), and
`tools/constants.txt` gives each action, command, flag and effect number its constant.
"scratch/..." scripts they mention were throwaway helpers, not kept.

| File | Classes |
|---|---|
| [core.md](core.md) | CPlayer, its frames (PatternFrame, PatternData), objects, the shared actions and commands, hit resolution |
| [game.md](game.md) | CGame, the scenes, effects, backgrounds, files, input, sound; game modes, key.ini, round and arcade flow |
| [akane-akiko-ayu-kanna.md](akane-akiko-ayu-kanna.md) | CAkane, CAkiko, CAyu, CKanna |
| [kano-ikumi-mishio-shiori.md](kano-ikumi-mishio-shiori.md) | CKano, CIkumi, CMishio, CShiori |
| [mizuka-mizukab-nayuki-nayukib.md](mizuka-mizukab-nayuki-nayukib.md) | CMizuka, CMizukaB, CNayuki, CNayukiB |
| [nanase-exnanase-nagamori-kaori.md](nanase-exnanase-nagamori-kaori.md) | CNanase, CEXNanase, CNagamori, CKaori |
| [misuzu-minagi-misaki-mio.md](misuzu-minagi-misaki-mio.md) | CMisuzu, CMinagi, CMisaki, CMio |
| [mai-makoto-mayu-sayuri.md](mai-makoto-mayu-sayuri.md) | CMai, CMakoto, CMayu, CSayuri |
