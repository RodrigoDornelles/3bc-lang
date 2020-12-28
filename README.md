3BC Lang
========
[![version](https://img.shields.io/github/v/release/rodrigodornelles/3bc-lang?sort=semver)](https://github.com/RodrigoDornelles/3bc-lang/releases)
[![license](https://img.shields.io/github/license/rodrigodornelles/3bc-lang)](https://github.com/RodrigoDornelles/3bc-lang/blob/master/LICENSE.txt) 
[![quality](https://app.codacy.com/project/badge/Grade/10888eee2fbc460b8ddb7476b0aceb23)](https://www.codacy.com/gh/RodrigoDornelles/3bc-lang/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RodrigoDornelles/3bc-lang&amp;utm_campaign=Badge_Grade)
[![covarage](https://codecov.io/gh/RodrigoDornelles/3bc-lang/branch/master/graph/badge.svg?token=FS152PL31C)](https://codecov.io/gh/RodrigoDornelles/3bc-lang)

> this is a machine language that has only 3 register bits for CPU, the idea is to make it so simple and intuitive that it can be easily read on punched cards.


* [view registers here](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md)


### Hello World Example ###
| Textual Programing | Octal Code |
| :----------------: | :--------: |
| `mode` `nill` `0x2`<br/>`strc` `nill` `'h'`<br/>`strc` `nill` `'e'`<br/>`strc` `nill` `'l'`<br/>`strc` `nill` `'l'`<br/>`strc` `nill` `'o'`<br/>`strc` `nill` `' '`<br/>`strc` `nill` `'w'`<br/>`strc` `nill` `'o'`<br/>`strc` `nill` `'r'`<br/>`strc` `nill` `'l'`<br/>`strc` `nill` `'d'`<br/>`strc` `nill` `'!'`  | `0o007` `0o000` `0o002`<br/>`0o002` `0o000` `0o150`<br/>`0o002` `0o000` `0o145`<br/>`0o002` `0o000` `0o154`<br/>`0o002` `0o000` `0o154`<br/>`0o002` `0o000` `0o157`<br/>`0o002` `0o000` `0o040`<br/>`0o002` `0o000` `0o167`<br/>`0o002` `0o000` `0o157`<br/>`0o002` `0o000` `0o162`<br/>`0o002` `0o000` `0o154`<br/>`0o002` `0o000` `0o144`<br/>`0o002` `0o000` `0o041` |

## Ambient Roadmap ##

 - [X] VM Memory auxiliary
 - [X] VM Output characters
 - [X] VM Memory Allocation 
 - [X] VM Input characters
 - [X] VM Memory Allocation 
 - [X] VM Mathematic Basics
 - [X] VM Labels
 - [X] VM Conditional Jumps
 - [X] Textual Interpreter just in time
 - [ ] Textual Interpreter to C transpiled
 - [ ] Textual Interpreter to binary
 - [ ] Programming IDE
 - [ ] Arduino Framework support
 - [ ] Includes support
 - [ ] Bindings support

## CPU Modes ##
although the CPU is limited only by 3 bits (8 registers in all), the main idea is to work with processing blocks as if there are multiple cpu nuclei where each one is specified in type of work.
| Channels | Architetures | Description |
| :------: | :----------: | :----------- |
| 0 | `dont use` | No Mode |
| [1](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md#debug-mode-1) [2](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md#string-mode-2) | x86 ARM RISC-V | character output |
| [3](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md#input-mode-3) [4](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md#input-silent-mode-4) [5](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md#input-silent-mode-4) |  x86 ARM | character input |
| [6](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md#memory-mode-6) | x86 ARM RISC-V | main memory |
| 7 | `dont use` | protected |
| [8](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md#memory-aux-mode-8) | x86 ARM RISC-V | aux memory |
| [9](https://github.com/RodrigoDornelles/3bc-lang/blob/master/INSTRUCTIONS.md#jump-mode-9) | x86 ARM RISC-V | logical jumps |
 * **x86:** conventional computer
 * **ARM:** smartphone, tv-box, raspbarry and similars
 * **RISC-V:** Arduino, ESP

## List of early developers ##
| **1º** | ![avatar](https://avatars.githubusercontent.com/rodrigodornelles?size=32) | **[Rodrigo Dornelles](https://github.com/rodrigodornelles)** | **26 November 2020** |
| :-: | :-: | :-- | :--: |
| **2º** | ![avatar](https://avatars.githubusercontent.com/kadu?size=32) | **[Carlos Eduardo](https://github.com/kadu)** | **28 November 2020** |
| **3º** |  ![avatar](https://avatars.githubusercontent.com/robsondrs?size=32) | **[Robson Soares](https://github.com/robsondrs)** | **23 December 2020** |
| **4º** |  ![avatar](https://avatars.githubusercontent.com/gnevesdev?size=32) | **[Guilherme Neves](https://github.com/gnevesdev)** | **28 December 2020** |
