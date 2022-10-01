3BC Language
============
[![sponsors](https://img.shields.io/github/sponsors/rodrigodornelles?color=ff69b4&logo=github)](https://github.com/sponsors/RodrigoDornelles)
[![version](https://img.shields.io/github/v/release/rodrigodornelles/3bc-lang?sort=semver&logo=github)](https://github.com/RodrigoDornelles/3bc-lang/releases)
[![license](https://img.shields.io/github/license/rodrigodornelles/3bc-lang?logo=gnu)](https://github.com/RodrigoDornelles/3bc-lang/blob/master/LICENSE.txt) 
[![covarage](https://img.shields.io/badge/coverage-99%25-brightgreen?logo=codecov)](docs/guide/warnings.md)

> Low-level language, tiny virtual machine, intermediate representation, embeddable, easy for beginners. (Friendly Punched cards)

## Documentation ##

* **[Tutorial :us:](docs/guide/tutorial-en-us.md)**
* **[Tutorial :brazil:](docs/guide/tutorial-pt-br.md)**
* **[Cheatsheet :book:](docs/guide/cheatsheet.md)**
* **[List of early developers :trophy:](docs/extra/early-adopters.md)**
* **[Visit the official website :globe_with_meridians:](https://3bc-lang.org)**

## Directory structure ##

If you are interested in exploring or contributing to the language, follow the monolithic organization.

```
docs/           Website made with jekyll (Ruby)
examples/       Syntax sampling codes (3bc, Arduino with C++)
programs/       Embbed programs sampling codes (C)
scripts/        Development and installation tools (Bash, Ruby)
src/            Library source code (C)
tests/          Language work check (Ruby)
```

## How to build ##

Download interpreter **source code** and manually compile from scratch.

```BASH
git clone https://github.com/RodrigoDornelles/3bc-lang
make build
```

## How to install ##

Directly download interpreter as **executable** command for mac/linux/bsd.

```BASH
sudo bash -c "$(wget -qO- https://raw.githubusercontent.com/RodrigoDornelles/3bc-lang/master/scripts/install_vm.sh || curl -fsSL https://raw.githubusercontent.com/RodrigoDornelles/3bc-lang/master/scripts/install_vm.sh)"
```

-------------------------------------------------
![3bc lang logo](/docs/images/3bc-logo-small.png)
This project is licensed under **GNU GPL 3.0 or higher**, please read the [LICENSE.txt](LICENSE.txt) file.
