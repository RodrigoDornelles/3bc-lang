3BC Language
============
[![version](https://img.shields.io/github/v/release/rodrigodornelles/3bc-lang?sort=semver)](https://github.com/RodrigoDornelles/3bc-lang/releases)
[![license](https://img.shields.io/github/license/rodrigodornelles/3bc-lang)](https://github.com/RodrigoDornelles/3bc-lang/blob/master/LICENSE.txt) 
[![quality](https://app.codacy.com/project/badge/Grade/10888eee2fbc460b8ddb7476b0aceb23)](https://www.codacy.com/gh/RodrigoDornelles/3bc-lang/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RodrigoDornelles/3bc-lang&amp;utm_campaign=Badge_Grade)
[![covarage](https://codecov.io/gh/RodrigoDornelles/3bc-lang/branch/master/graph/badge.svg?token=FS152PL31C)](https://codecov.io/gh/RodrigoDornelles/3bc-lang)
[![Build Status](https://img.shields.io/github/checks-status/rodrigodornelles/3bc-lang/master)](https://github.com/rodrigodornelles/3bc-lang/actions)

> Low-level language, tiny virtual machine, intermediate representation, embeddable, easy for beginners. (Friendly Punched cards)

## Directory structure ##

```
docs/           Website made with jekyll (Ruby)
examples/       Syntax sampling codes (3bc, Arduino with C++)
programs/       Embbed programs sampling codes (C)
scripts/        Development and installation tools (Bash, Ruby)
src/            Library source code (C)
tests/          Language work check (Ruby)
```

## Documentation ##

* **[Tutorial :us:](https://3bc-lang.org/guide/tutorial-en-us)**
* **[Tutorial :brazil:](https://3bc-lang.org/guide/tutorial-pt-br)**
* **[Cheatsheet](https://3bc-lang.org/guide/cheatsheet)**
* **[Changelogs](https://3bc-lang.org/extra/changelogs)**
* **[Ambient Roadmap](https://3bc-lang.org/extra/roadmap)**
* **[Platform Support](https://3bc-lang.org/support)**
* **[How to "Hello World"](https://3bc-lang.org/guide/tutorial-en-us#how-to-hello-world)**
* **[Download last version](https://3bc-lang.org/download)**
* **[List of early developers](https://3bc-lang.org/extra/early-adopters)**

## How to build ##

Download interpreter source code and manually compile from scratch.

```BASH
git clone https://github.com/RodrigoDornelles/3bc-lang
make build
```

## Hot to install ##

Directly download interpreter as executable command for mac/linux/bsd.

```BASH
sudo bash -c "$(wget -qO- https://raw.githubusercontent.com/RodrigoDornelles/3bc-lang/master/scripts/install_vm.sh || curl -fsSL https://raw.githubusercontent.com/RodrigoDornelles/3bc-lang/master/scripts/install_vm.sh)"
```

-----------------------------------------------------------------------------------------
![3bc lang logo](/docs/images/3bc-logo-small.png)
This project is licensed under **GNU GPL 3.0 or higher**, please read the [LICENSE.txt](LICENSE.txt) file.
