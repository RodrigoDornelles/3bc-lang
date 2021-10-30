3BC Language
============
[![version](https://img.shields.io/github/v/release/rodrigodornelles/3bc-lang?sort=semver)](https://github.com/RodrigoDornelles/3bc-lang/releases)
[![license](https://img.shields.io/github/license/rodrigodornelles/3bc-lang)](https://github.com/RodrigoDornelles/3bc-lang/blob/master/LICENSE.txt) 
[![quality](https://app.codacy.com/project/badge/Grade/10888eee2fbc460b8ddb7476b0aceb23)](https://www.codacy.com/gh/RodrigoDornelles/3bc-lang/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RodrigoDornelles/3bc-lang&amp;utm_campaign=Badge_Grade)
[![covarage](https://codecov.io/gh/RodrigoDornelles/3bc-lang/branch/master/graph/badge.svg?token=FS152PL31C)](https://codecov.io/gh/RodrigoDornelles/3bc-lang)
[![Build Status](https://img.shields.io/github/checks-status/rodrigodornelles/3bc-lang/master)](https://github.com/rodrigodornelles/3bc-lang/actions)

> Low level language, tiny virtual machine that works on computers and microcontrollers. (Friendly Punched cards)

| Common questions | answer |
| :--------------- | :----- |
| What is the purpose of the language? | the idea is to be a low level, simple and intuitive language that anyone can learn! (and that can even be read on punched cards) |
| Do you need knowledge of **C** to understand 3BC? | No, they have different syntaxes |
| What is the language's typing level ? | There is no distinction of types, they are just data |
| Does it have garbage collector? | No, the developer has full control over the memory, this follows the same philosophy as **C** "freedom with responsibility" |
| Does it work as a compiler? | No, it currently works as an interpreter (although a very fast one), or also by packaging bytecode with a vm in a single binary. |
| What are the influences? | Languages **Cobol**, **Ruby** and **Java**; Assembly´s **WASM**, **ARM** and **x86** |
| Is it more compact than **Lua**? | Yeah, because it has the same performance target as the Arduino Uno microcontroller. And this impacts it's size (depending on the CPU's architecture, 14KiB ROM and 400 bytes RAM ) |

## Documentation ##

* **[Tutorial :us:](docs/tutorial-en-us.md)**
* **[Tutorial :brazil:](docs/tutorial-pt-br.md)**
* **[Cheatsheet](docs/cheatsheet.md)**
* **[Changelogs](docs/changelogs.md)**
* **[Platform Support](support.md)**
* **[Download last version](download.md)**
* **[Ambient Roadmap](#ambient-roadmap)**
* **[How to "Hello World"](#how-to-hello-world)**
* **[List of early developers](#list-of-early-developers)**

## How to "Hello World" ##

These steps will guide you to run the hello world example and to have your first 3BC program running in your machine, let get's started.

After downloading the binary on the [releases](#https://github.com/RodrigoDornelles/3bc-lang/releases) page, just decompress the file and utilize the command line to interpret the source code using the compiler according to your operating system: [windows](#windows),[mac osx](#mac--unix--linux), [unix](#mac--unix--linux), [linux](#mac--unix--linux)

### example: `helloworld.3bc` ###

```RUBY
mode nill 0d2
strc nill 'h'
strc nill 'e'
strc nill 'l'
strc nill 'l'
strc nill 'o'
strc nill ' '
strc nill 'w'
strc nill 'o'
strc nill 'r'
strc nill 'l'
strc nill 'd'
strc nill '!'
```

### windows ###

```
C:\Users\nicod\Downloads\3bc-windows-32>3bc.exe helloworld.3bc
hello world!
C:\Users\nicod\Downloads\3bc-windows-32>
```

### mac / unix / linux ###

```
$ ./3bc helloworld.3bc
hello world!
$
```
