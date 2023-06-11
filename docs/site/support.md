---
description: List of all platforms that are working, or that will receive the support soon.
---

Platform Support List
=====================

Computers
------------------

|              | i386  | amd64 | arm32 | arm64 | mips32 | mips64 | powerpc | powerpc64 | riscv | riscv64 | s390x |
| :----------- | :---: | :---: | :---: | :---: | :----: | :----: | :-----: | :-------: | :---: | :-----: | :---: |
| Android      | _N/A_ | :ok:  | :ok:  | :ok:  | _N/A_  | _N/A_  | _N/A_   | _N/A_     | _N/A_ | _N/A_   | _N/A_ |
| Windows      | :ok:  | :ok:  | _N/A_ | :ok:  | _N/A_  | _N/A_  | _N/A_   | _N/A_     | _N/A_ | _N/A_   | _N/A_ |
| Mac OS       | :x:   | :ok:  | _N/A_ | :ok:  | _N/A_  | _N/A_  |         | _N/A_     | _N/A_ | _N/A_   | _N/A_ |
| Docker Linux | :ok:  | :ok:  | :ok:  | :ok:  |        | :ok:   |         | :ok:      |       |         | :ok:  |
| GNU Linux    | :ok:  | :ok:  | :ok:  | :ok:  | :ok:   |        | :ok:    | :ok:      |       | :ok:    |       | 
| GNU Hurd     |       |       |       |       |        |        |         |           |       |         | _N/A_ |
| Plan 9       |       |       |       |       |        |        |         |           |       |         | _N/A_ |
| Open BSD     |       |       |       |       |        |        |         |           |       |         | _N/A_ |
| Free BSD     | :x:   | :x:   |       |       |        |        |         |           |       |         | _N/A_ |

 1. **mac os** does not support 32-bit systems.
 2. **windows** windows is not currently supporting cpu sleep mode.
 3. **freebsd** currently does not support official publication.

Integrations
------------

|         | wasm | wasm.js<br/>_(legacy)_ | emscripten<br/>_(bloated)_ | typescript |
| :------ | :--: | :--------------------: | :------------------------: | :--------: |
| NodeJS  |      |                        | :ok:                       |            |
| Browser |      |                        |                            |            |


|                 | C++   | NodeJS | Python | Rust |
| :-------------- | :---: | :----: | :----: | :--: |
| FFI             | _N/A_ |        |        |      |
| Wrapper         |       |        |        | :ok: |
| Dynamic Library |       |        |        |      |

 * **Rust** third-party support <https://github.com/yxqsnz/3bc-sys>

Embedded Systems
----------------

|           | avr   | riscv | arm   | pic   |
| :-------- | :---: | :---: | :---: | :-:   |
| Arduino   | :ok:  | :ok:  | :ok:  | _N/A_ |
| AVR Lib C | :ok:  | _N/A_ | _N/A_ | _N/A_ |
| ESP IDF   | _N/A_ | :ok:  | _N/A_ | _N/A_ |
| ODroid    |       |       |       | _N/A_ |
| Free RTOS |       | :ok:  |       | _N/A_ |
| Baremetal |       |       |       |       |

Legacy Systems
--------------

|               | i386  | mos6502<br/>NES | mos6502<br/>Apple 2 | mos6502<br/>C64 |
| :------------ | :---: | :-------------: | :-----------------: | :-------------: |
| Baremetal     | _N/A_ | :ok:            | :ok:                |                 |
| Microsoft Dos |       | _N/A_           |                     |                 |

 * **MOS6502 / Nintendo Entertainment System** currently it only runs hello world compiled together with the virtual machine program.
 * **MOS6502 / Apple 2** runs programs that are compiled together with the virtual machine and without support interpreter or repl.
