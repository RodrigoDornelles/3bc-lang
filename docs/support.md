---
description: List of all platforms that are working, or that will receive the support soon.
---

Platform Support List
=====================

Computers
------------------

|              | i386 | amd64 | arm32 | arm64 | mips32 | mips64 | powerpc | powerpc64 | riscv | riscv64 | s390x |
| :----------- | :--: | :---: | :---: | :---: | :----: | :----: | :-----: | :-------: | :---: | :-----: | :---: |
| Windows      | :ok: | :ok:  |       | :ok:  | _N/A_  | _N/A_  | _N/A_   | _N/A_     | _N/A_ | _N/A_   | _N/A_ |
| Mac OS       | :x:  | :ok:  |       | :ok:  | _N/A_  | _N/A_  | _N/A_   | _N/A_     | _N/A_ | _N/A_   | _N/A_ |
| Docker Linux | :ok: | :ok:  | :ok:  | :ok:  |        | :ok:   |         | :ok:      |       |         | :ok:  |
| GNU Linux    | :ok: | :ok:  | :ok:  | :ok:  | :ok:   |        | :ok:    | :ok:      |       | :ok:    |       | 
| GNU Hurd     |      |       |       |       |        |        |         |           |       |         | _N/A_ |
| Plan 9       |      |       |       |       |        |        |         |           |       |         | _N/A_ |
| Open BSD     |      |       |       |       |        |        |         |           |       |         | _N/A_ |
| Free BSD     | :x:  | :x:   |       |       |        |        |         |           |       |         | _N/A_ |

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

 * **rust** third-party support <https://github.com/yxqsnz/3bc-sys>

Embedded Systems
----------------

| system | architeture | working | running | released |
| :----- | :---------: | :-----: | :-----: | :------: |
| AVR Libc | avr | :ok: |
| Arduino | avr | :ok: | :ok: | :ok: |
| Arduino | risc-v | :ok: | :ok: | :ok: |
| Free RTOS | risc-v |
| ESP IDF | risc-v |
| NuttX | arm | :ok: | :ok: |
| NuttX | avr | :ok: | :ok: |
| NuttX | risc-v | :ok: | :ok: |
| ODroid | risc-v |

Legacy Systems
--------------

| system | architeture | working | running | released |
| :----- | :---------: | :-----: | :-----: | :------: |
| Microsoft DOS | i386 |
| Apple 2 | mos6502 | :ok: |
| Commodore 64 | mos6502 |
| Nintendo Entertainment System | mos6502 |
