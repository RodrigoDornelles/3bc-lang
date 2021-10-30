3BC Language
============
[![version](https://img.shields.io/github/v/release/rodrigodornelles/3bc-lang?sort=semver)](https://github.com/RodrigoDornelles/3bc-lang/releases)
[![license](https://img.shields.io/github/license/rodrigodornelles/3bc-lang)](https://github.com/RodrigoDornelles/3bc-lang/blob/master/LICENSE.txt) 
[![quality](https://app.codacy.com/project/badge/Grade/10888eee2fbc460b8ddb7476b0aceb23)](https://www.codacy.com/gh/RodrigoDornelles/3bc-lang/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RodrigoDornelles/3bc-lang&amp;utm_campaign=Badge_Grade)
[![covarage](https://codecov.io/gh/RodrigoDornelles/3bc-lang/branch/master/graph/badge.svg?token=FS152PL31C)](https://codecov.io/gh/RodrigoDornelles/3bc-lang)
[![Build Status](https://img.shields.io/github/checks-status/rodrigodornelles/3bc-lang/master)](https://github.com/rodrigodornelles/3bc-lang/actions)

> ![3bc lang logo](/docs/images/3bc-logo-small.png)
> Low level language, tiny virtual machine that works on computers and microcontrollers. (Friendly Punched cards)

## Documentation ##

* **[Tutorial :us:](https://3bc-lang.org/guide/tutorial-en-us)**
* **[Tutorial :brazil:](https://3bc-lang.org/guide/tutorial-pt-br)**
* **[Cheatsheet](https://3bc-lang.org/guide/cheatsheet.md)**
* **[Changelogs](https://3bc-lang.org/extra/changelogs.md)**
* **[Ambient Roadmap](https://3bc-lang.org/extra/roadmap)**
* **[Platform Support](https://3bc-lang.org/support.md)**
* **[How to "Hello World"](#how-to-hello-world)**
* **[Download last version](https://3bc-lang.org/download)**
* **[List of early developers](https://3bc-lang.org/early-adopters)**

| Common questions | answer |
| :--------------- | :----- |
| What is the purpose of the language? | the idea is to be a low level, simple and intuitive language that anyone can learn! (and that can even be read on punched cards) |
| Do you need knowledge of **C** to understand 3BC? | No, they have different syntaxes |
| What is the language's typing level ? | There is no distinction of types, they are just data |
| Does it have garbage collector? | No, the developer has full control over the memory, this follows the same philosophy as **C** "freedom with responsibility" |
| Does it work as a compiler? | No, it currently works as an interpreter (although a very fast one), or also by packaging bytecode with a vm in a single binary. |
| What are the influences? | Languages **Cobol**, **Ruby** and **Java**; Assembly´s **WASM**, **ARM** and **x86** |
| Is it more compact than **Lua**? | Yeah, because it has the same performance target as the Arduino Uno microcontroller. And this impacts it's size (depending on the CPU's architecture, 14KiB ROM and 400 bytes RAM ) |
