# Elijah C. Voigt | CS362 Winter 2016 | Dominion Game

## Setup

This repository makes [upstream
changes](https://github.com/CS362-Winter-2016/cs362w16core) readily available
via [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

When you clone the repository run the following commands to *also* clone the
submodule `upstream`.

```
$ git clone https://github.com/CS362-Winter-2016/cs362w16_voigte.git
[... cloning output ...]
$ git submodule init .
[... git submodule cloning output ...]
$ ls
dominion  README.md  upstream
```

You don't need the submodule to use my dominion code, it's just there if you
care.

Changes are documented in `refactor.txt` as well the `git log` of this repo.
`refactor.txt` is a bit more verbose.
