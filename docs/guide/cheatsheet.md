CheatSheet
==========

| Mode | Name | Description | Instructions |
| :--: | :--: | :---------- | :----------- |
| 0 | <br/> | not use | `nill` `mode` |
| 1 | **[MODE_DEBUG](#mode-debug)** | depuration put char | `nill` `strb` `stro` `stri` `strx` `strc` `mode` |
| 2 | **[MODE_STRING](#mode-string)** | console put char | `nill` `strb` `stro` `stri` `strx` `strc` `mode` |
| 3 | **[MODE_INPUT](#mode-input)** | console input keyboard | `nill` `strb` `stro` `stri` `strx` `strc` `mode` |
| 4 | **[MODE_INPUT_SILENT](#mode-input-silent)** | console input keyboard (silent) | `nill` `strb` `stro` `stri` `strx` `strc` `mode` |
| 5 | **[MODE_INPUT_PASSWORD](#mode-input-password)** | console input keyboard (password) | `nill` `strb` `stro` `stri` `strx` `strc` `mode` |
| 6 | **[MODE_MEMORY](#mode-memory)** | main memory controller | `nill` `free` `aloc` `moff` `muse` `mmax` `tmin` `mode` |
| 7 | **[MODE_MEMORY_PTR](#mode-memory-ptr)** | pointers memory controller | `nill` `free` `aloc` `pull` `spin` `push` `mode` |
| 8 | **[MODE_MEMORY_AUX](#mode-memory-aux)** | aux memory controller | `nill` `free` `aloc` `pull` `spin` `push` `mode` |
| 9 | **[MODE_JUMP](#mode-jump)** | logical jumps between labels | `nill` `goto` `fgto` `zgto` `pgto` `ngto` `mode` |
| 10 | <br/> | reserved | <br/> |
| 11 | **[MODE_MATH_SUM](#mode-math-sum)** | basic mathematic sum  | `nill` `math` `mode` |
| 12 | **[MODE_MATH_SUB](#mode-math-sub)** | basic mathematic subtration  | `nill` `math` `mode` |
| 13 | **[MODE_MATH_MUL](#mode-math-mul)** | basic mathematic multiplication | `nill` `math` `mode` |
| 14 | **[MODE_MATH_DIV](#mode-math-div)** | basic mathematic division  | `nill` `math` `mode` |
| 15 | **[MODE_MATH_MOD](#mode-math-mod)** | basic mathematic rest of division  | `nill` `math` `mode` |
| 16 | **[MODE_MATH_POWER](#mode-math-power)** | basic mathematic power | `nill` `math` `mode` |
| 17 | **[MODE_MATH_ROOT](#mode-math-root)** | basic mathematic root | `nill` `math` `mode` |
| 18 | **[MODE_MATH_ABS](#mode-math-abs)** | basic mathematic module | `nill` `math` `mode` |
| 29 | **[MODE_HELPER_MUL_ADD](#mode-helper-mul-add)** | multiply by base and add acumulator | `nill` `nb02` `nb08` `nb10` `nb16` `mode` |
| 20 | <br/> | reserved | <br/> |
| 21 | **[MODE_BITWISE_NOT](#mode-bitwise-not)** | boolean not (per bit) | `nill` `math` `mode` |
| 22 | **[MODE_BITWISE_AND](#mode-bitwise-and)** | boolean and (per bit) | `nill` `math` `mode` |
| 23 | **[MODE_BITWISE_OR](#mode-bobitwiseol-or)** | boolean or (per bit) | `nill` `math` `mode` |
| 24 | **[MODE_BITWISE_XOR](#mode-bitwise-xor)** | boolean xor (per bit) | `nill` `math` `mode` |
| 25 | **[MODE_BITWISE_NAND](#mode-bitwise-nand)** | boolean nand (per bit)  | `nill` `math` `mode` |
| 26 | **[MODE_BITWISE_NOR](#mode-bitwise-nor)** | boolean nor (per bit) | `nill` `math` `mode` |
| 27 | **[MODE_BITWISE_XNOR](#mode-bitwise-xnor)** | boolean xnor (per bit) | `nill` `math` `mode` |
| 28 | **[MODE_BITWISE_LEFT](#mode-bitwise-left)** | bit shift left | `nill` `math` `mode` |
| 29 | **[MODE_BITWISE_LEFT](#mode-bitwise-right)** | bit shift right | `nill` `math` `mode` |
| 30 | <br/> | reserved | <br/> |
| 31 | **[MODE_BOOLEAN_NOT](#mode-boolean-not)** | boolean not | `nill` `math` `mode` |
| 32 | **[MODE_BOOLEAN_AND](#mode-boolean-and)** | boolean and | `nill` `math` `mode` |
| 33 | **[MODE_BOOLEAN_OR](#mode-boolean-or)** | boolean or | `nill` `math` `mode` |
| 34 | **[MODE_BOOLEAN_XOR](#mode-boolean-xor)** | boolean xor | `nill` `math` `mode` |
| 35 | **[MODE_BOOLEAN_NAND](#mode-boolean-nand)** | boolean nand  | `nill` `math` `mode` |
| 36 | **[MODE_BOOLEAN_NOR](#mode-boolean-nor)** | boolean nor | `nill` `math` `mode` |
| 37 | **[MODE_BOOLEAN_XNOR](#mode-boolean-xnor)** | boolean xnor | `nill` `math` `mode` |
| 38 | **[MODE_LOG_BASE](#mode-log-base)** | logarithm in base n | `nill` `math` `mode` |
| 39 | **[MODE_LOG_NATURAL](#mode-log-natural)** | natural logarithm | `nill` `math` `mode` |
| 40 | <br/> | reserved | <br/> |
| 41 | **[MODE_PROCEDURE_RET](#mode-procedure-ret)** | procedure return | `nill` `back` `fret` `zret` `pret` `nret` `mode` |
| 42 | **[MODE_PROCEDURE](#mode-procedure)** | procedure call | `nill` `call` `fcal` `zcal` `pcal` `ncal` `mode` |
| 43 | **[MODE_SLEEP](#mode-sleep)** | inactive cpu for a periodt of time | `nill` `real` `fake` `micr` `mili` `seco` `mode` |

# Architecture details  #

## COMMON ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `nill` | 0 | 000 | label reference point or skip line (null) |
| `mode` | 7 | 111 | change cpu register bank |

## NO MODE `DONT USE` ##

## MODE DEBUG ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | log number as binary |
| `stro` | 2 | 010 | log number as octal |
| `stri` | 3 | 011 | log number as decimal |
| `strx` | 4 | 100 | log number as hexadecimal |
| `strc` | 5 | 101 | log ascii character |

* **Number:** 0o01 0d01 0x01

## MODE STRING ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | put number as binary |
| `stro` | 2 | 010 | put number as octal |
| `stri` | 3 | 011 | put number as decimal |
| `strx` | 4 | 100 | put number as hexadecimal |
| `strc` | 5 | 101 | put ascii character |

* **Number:** 0o02 0d02 0x02

## MODE INPUT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | input number as binary |
| `stro` | 2 | 010 | input number as octal |
| `stri` | 3 | 011 | input number as decimal |
| `strx` | 4 | 100 | input number as hexadecimal |
| `strc` | 5 | 101 | input ascii character |


* **Number:** 0o03 0d03 0x03

## MODE INPUT SILENT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | input number as binary |
| `stro` | 2 | 010 | input number as octal |
| `stri` | 3 | 011 | input number as decimal |
| `strx` | 4 | 100 | input number as hexadecimal |
| `strc` | 5 | 101 | input ascii character |

* **Number:** 0o04 0d04 0x04

## MODE INPUT PASSWORD ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | input number as binary |
| `stro` | 2 | 010 | input number as octal |
| `stri` | 3 | 011 | input number as decimal |
| `strx` | 4 | 100 | input number as hexadecimal |
| `strc` | 5 | 101 | input ascii character |

* **Number:** 0o05 0d05 0x05

## MODE MEMORY ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `free` | 1 | 001 | realese memory |
| `aloc` | 2 | 010 | reserve memory and set a value |
| `moff` | 3 | 011 | memory config remove mask |
| `muse` | 4 | 100 | memory config append mask |
| `mmax` | 5 | 101 | set max value allowed in memory |
| `mmin` | 6 | 110 | set min value allowed in memory |

* **Number:** 0o06 0d06 0x06

## MODE MEMORY PTR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `free` | 1 | 001 | realese memory in pointer |
| `aloc` | 2 | 010 | set a value in pointer |
| `pull` | 3 | 011 | pull aux memory to address pointer memory (ptr <- aux) |
| `spin` | 4 | 100 | inverse values inner memory pointer and aux (ptr <-> aux) |
| `push` | 5 | 101 | push aux memory to pointer memory (ptr -> aux) |


* **Number:** 0o07 0d07 0x07

## MODE MEMORY AUX ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `free` | 1 | 001 | realese memory aux |
| `aloc` | 2 | 010 | set a value in aux memory |
| `pull` | 3 | 011 | pull aux memory to address memory (addr <- aux) |
| `spin` | 4 | 100 | inverse values inner memory and aux (addr <-> aux) |
| `push` | 5 | 101 | push aux memory to address memory (addr -> aux) |


* **Number:** 0o10 0d08 0x08

## MODE JUMP ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `goto` | 1 | 001 | jump to the label unconditionally |
| `fgto` | 2 | 010 | jump to the label if aux memory is fill |
| `zgto` | 3 | 011 | jump to the label if aux memory is empty |
| `pgto` | 4 | 100 | jump to the label if aux memory is positive |
| `ngto` | 5 | 101 | jump to the label if aux memory is negative |

* **Number:** 0o11 0d09 0x09

## MODE MATH SUM ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | add value in the aux memory |

* **Number:** 0o13 0d11 0x0B

## MODE MATH SUB ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | subtraction in the aux memory |

* **Number:** 0o14 0d12 0x0C

## MODE MATH MUL ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | multiplication in the aux memory |

* **Number:** 0o15 0d13 0x0D

## MODE MATH DIV ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | division in the aux memory |

* **Number:** 0o16 0d14 0x0E

## MODE MATH MOD ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | rest of the division with aux memory |

* **Number:** 0o17 0d15 0x0F

## MODE MATH POWER ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | enhance aux memory value |

* **Number:** 0o20 0d16 0x10

## MODE MATH ROOT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | root aux memory value |

* **Number:** 0o21 0d17 0x11

## MODE MATH ABS ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | module positive aux memory value |

* **Number:** 0o23 0d18 0x12

## MODE HELPER MUL ADD ##

| name | octal | bit | description |
| ------ | - | --- | - |
| `nb02` | 1 | 001 | multiply by 2 and accumulate operation |
| `nb08` | 2 | 010 | multiply by 8 and accumulate operation |
| `nb10` | 3 | 011 | multiply by 10 and accumulate operation |
| `nb16` | 4 | 100 | multiply by 16 and accumulate operation |

* **Number:** 0o23 0d19 0x13

## MODE BITWISE NOT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean not (per bit) |

* **Number:** 0o25 0d21 0x15

## MODE BITWISE AND ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean and (per bit) |

* **Number:** 0o26 0d22 0x16

## MODE BITWISE OR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean or (per bit) |

* **Number:** 0o26 0d23 0x17

## MODE BITWISE XOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean xor (per bit) |

* **Number:** 0o27 0d24 0x18

## MODE BITWISE NAND ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean nand (per bit) |

* **Number:** 0o30 0d25 0x19

## MODE BITWISE NOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean nor (per bit) |

* **Number:** 0o31 0d26 0x1A

## MODE BITWISE XNOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean xnor |

* **Number:** 0o32 0d27 0x1B

## MODE BITWISE LEFT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux bit shift left |

* **Number:** 0o33 0d28 0x1C

## MODE BITWISE LEFT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux bit shift right |

* **Number:** 0o34 0d29 0x1D

## MODE BOOLEAN NOT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean not |

* **Number:** 0o37 0d31 0x1F

* **Truth table**

| aux | !aux |
| :-: | :-: |
| 0 | 1 |
| 1 | 0 |

## MODE BOOLEAN AND ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean and |

* **Number:** 0o40 0d32 0x20

* **Truth table**

| aux | math | aux * math |
| :-: | :--: | :--------: |
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

## MODE BOOLEAN OR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean or |

* **Number:** 0o41 0d33 0x21

* **Truth table**

| aux | math | aux + math |
| :-: | :--: | :--------: |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

## MODE BOOLEAN XOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean xor |

* **Number:** 0o42 0d34 0x22

* **Truth table**

| aux | math | aux (+) math |
| :-: | :--: | :----------: |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

## MODE BOOLEAN NAND ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean nand |

* **Number:** 0o43 0d35 0x23

* **Truth table**

| aux | math | !(aux * math) |
| :-: | :--: | :-----------: |
| 0 | 0 | 1 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

## MODE BOOLEAN NOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean nor |

* **Number:** 0o44 0d36 0x24

* **Truth table**

| aux | math | !(aux + math) |
| :-: | :--: | :-----------: |
| 0 | 0 | 1 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 0 |

## MODE BOOLEAN XNOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | aux boolean xnor |

* **Number:** 0o45 0d37 0x25

* **Truth table**

| aux | math | !(aux (+) math) |
| :-: | :--: | :-----------: |
| 0 | 0 | 1 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

## MODE LOG BASE ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | log aux in base n |

* **Number:** 0o46 0d38 0x26

## MODE LOG NATURAL ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | log aux natural |

* **Number:** 0o48 0d39 0x27

## MODE PROCEDURE_RET ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `call` | 1 | 001 | return from procedure unconditionally |
| `fcal` | 2 | 010 | return from procedure if aux memory is fill |
| `zcal` | 3 | 011 | return from procedure if aux memory is empty |
| `pcal` | 4 | 100 | return from procedure if aux memory is positive |
| `ncal` | 5 | 101 | return from procedure if aux memory is negative |

* **Number:** 0o51 0d41 0x29

## MODE PROCEDURE ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `call` | 1 | 001 | call label procedure unconditionally |
| `fcal` | 2 | 010 | call label procedure if aux memory is fill |
| `zcal` | 3 | 011 | call label procedure if aux memory is empty |
| `pcal` | 4 | 100 | call label procedure if aux memory is positive |
| `ncal` | 5 | 101 | call label procedure if aux memory is negative |

* **Number:** 0o52 0d42 0x2A

## MODE SLEEP ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `real` | 1 | 001 | inactive cpu for x cycles (real hardware) |
| `fake` | 2 | 010 | inactive cpu for x cycles (virtual machine) |
| `micr` | 3 | 011 | inactive cpu for x microseconds |
| `mili` | 4 | 100 | inactive cpu for x milliseconds |
| `seco` | 5 | 101 | inactive cpu for x seconds |

* **Number:** 0o53 0d43 0xB

* **Note**: there may be an inaccuracy for values ​​less than 1 millisecond (depends of hardware).
