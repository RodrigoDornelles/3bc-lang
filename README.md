3BC Lang
========
[![version](https://img.shields.io/github/v/release/rodrigodornelles/3bc-lang?sort=semver)](https://github.com/RodrigoDornelles/3bc-lang/releases)
[![license](https://img.shields.io/github/license/rodrigodornelles/3bc-lang)](https://github.com/RodrigoDornelles/3bc-lang/blob/master/LICENSE.txt) 
[![quality](https://app.codacy.com/project/badge/Grade/10888eee2fbc460b8ddb7476b0aceb23)](https://www.codacy.com/gh/RodrigoDornelles/3bc-lang/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RodrigoDornelles/3bc-lang&amp;utm_campaign=Badge_Grade)
[![covarage](https://codecov.io/gh/RodrigoDornelles/3bc-lang/branch/master/graph/badge.svg?token=FS152PL31C)](https://codecov.io/gh/RodrigoDornelles/3bc-lang)

> this is a machine language that has only 3 register bits for CPU, the idea is to make it so simple and intuitive that it can be easily read on punched cards.

# How to "Hello World" #
This steps will guide you to run the hello world example and have first 3bc program running in your machine,  let get's started

After download the binary on release session, just decompress on folder and execute from command line:
change the [filename.3bc] to file that you want to execute, you can use one source file from the examples folder like helloworld.3bc

### windows ###
3bc.exe [filename.3bc]
```
C:\Users\nicod\Downloads\3bc-windows-32>3bc.exe helloworld.3bc
hello world!
C:\Users\nicod\Downloads\3bc-windows-32>
```

### mac / linux / unix ###
./3bc [filename.3bc]
```
$ ./3bc helloworld.3bc
hello world!
$
```

## Preview Concept ##
| Textual Programing | Octal Code |
| :----------------: | :--------: |
| `mode` `nill` `0x2`<br/>`strc` `nill` `'h'`<br/>`strc` `nill` `'e'`<br/>`strc` `nill` `'l'`<br/>`strc` `nill` `'l'`<br/>`strc` `nill` `'o'`<br/>`strc` `nill` `' '`<br/>`strc` `nill` `'w'`<br/>`strc` `nill` `'o'`<br/>`strc` `nill` `'r'`<br/>`strc` `nill` `'l'`<br/>`strc` `nill` `'d'`<br/>`strc` `nill` `'!'`  | `0o007` `0o000` `0o002`<br/>`0o002` `0o000` `0o150`<br/>`0o002` `0o000` `0o145`<br/>`0o002` `0o000` `0o154`<br/>`0o002` `0o000` `0o154`<br/>`0o002` `0o000` `0o157`<br/>`0o002` `0o000` `0o040`<br/>`0o002` `0o000` `0o167`<br/>`0o002` `0o000` `0o157`<br/>`0o002` `0o000` `0o162`<br/>`0o002` `0o000` `0o154`<br/>`0o002` `0o000` `0o144`<br/>`0o002` `0o000` `0o041` |

# Documentation #
* **[clice here](/docs/README.md)**

# Ambient Roadmap #
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


# List of early developers #
| **1º** | ![avatar](https://avatars.githubusercontent.com/rodrigodornelles?size=32) | **[Rodrigo Dornelles](https://github.com/rodrigodornelles)** | **26 November 2020** |
| :-: | :-: | :-- | :--: |
| **2º** | ![avatar](https://avatars.githubusercontent.com/kadu?size=32) | **[Carlos Eduardo](https://github.com/kadu)** | **28 November 2020** |
| **3º** |  ![avatar](https://avatars.githubusercontent.com/robsondrs?size=32) | **[Robson Soares](https://github.com/robsondrs)** | **23 December 2020** |
| **4º** |  ![avatar](https://avatars.githubusercontent.com/gnevesdev?size=32) | **[Guilherme Neves](https://github.com/gnevesdev)** | **28 December 2020** |
| **5º** |  ![avatar](https://avatars.githubusercontent.com/marcusmmmz?size=32) | **[Marcus Paulo](https://github.com/marcusmmmz)** | **30 December 2020** |
| **6º** |  ![avatar](https://avatars.githubusercontent.com/keshizin?size=32) | **[Takeshi Ishikawa](https://github.com/keshizin)** | **30 December 2020** |
| **7º** |  ![avatar](https://avatars.githubusercontent.com/andreluispy?size=32) | **[André Luis](https://github.com/andreluispy)** | **31 December 2020** |
