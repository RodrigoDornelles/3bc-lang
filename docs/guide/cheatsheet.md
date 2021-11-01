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
| 19 | **[MODE_MATH_NEGATIVE](#mode-math-abs)** | basic mathematic negative | `nill` `math` `mode` |
| 20 | <br/> | reserved | <br/> |
| 21 | **[MODE_HELPER_AVERAGE](#mode-helper-average)** | helper mathematic avarege | `nill` `math` `mode` |
| 18 | **[MODE_HELPER_SIGN](#mode-helper-sign)** | helper mathematic sign | `nill` `math` `mode` |
| 23 | **[MODE_HELPER_MAX](#mode-helper-max)** | helper mathematic maximum  | `nill` `math` `mode` |
| 24 | **[MODE_HELPER_MIN](#mode-helper-min)** | helper mathematic minimum | `nill` `math` `mode` |
| 25 | **[MODE_HELPER_PERCENTAGE](#mode-helper-percentage)** | helper mathematic percentage | `nill` `math` `mode` |
| 26 | **[MODE_HELPER_REVERSE](#mode-helper-reverse)** | helper base reverse | `nill` `nb02` `nb08` `nb10` `nb16` `mode` |
| 27 | **[MODE_HELPER_LOG2](#mode-helper-log-base-2)** | helper log base 2 | `nill` `math` `mode` |
| 28 | **[MODE_HELPER_LOG10](#mode-helper-log-base-10)** | helper log base 10 | `nill` `math` `mode` |
| 29 | **[MODE_HELPER_MUL_ADD](#mode-helper-mul-add)** | multiply by base and add acumulator | `nill` `nb02` `nb08` `nb10` `nb16` `mode` |
| 30 | <br/> | reserved | <br/> |
| 31 | **[MODE_BOOL_NOT](#mode-bool-not)** | boolean not | `nill` `math` `mode` |
| 32 | **[MODE_BOOL_AND](#mode-bool-and)** | boolean and | `nill` `math` `mode` |
| 33 | **[MODE_BOOL_OR](#mode-bool-or)** | boolean or | `nill` `math` `mode` |
| 34 | **[MODE_BOOL_XOR](#mode-bool-xor)** | boolean xor | `nill` `math` `mode` |
| 35 | **[MODE_BOOL_NAND](#mode-bool-nand)** | boolean nand  | `nill` `math` `mode` |
| 36 | **[MODE_BOOL_NOR](#mode-bool-nor)** | boolean nor | `nill` `math` `mode` |
| 37 | **[MODE_BOOL_XNOR](#mode-bool-xnor)** | boolean xnor | `nill` `math` `mode` |
| 38 | **[MODE_BOOL_AND_NOT](#mode-bool-and-not)** | boolean and not | `nill` `math` `mode` |
| 39 | **[MODE_BOOL_OR_NOT](#mode-bool-or-not)** | boolean or not | `nill` `math` `mode` |
| 40 | <br/> | reserved | <br/> |
| 41 | **[MODE_PROCEDURE_RET](#mode-procedure-ret)** | procedure return | `nill` `back` `fret` `zret` `pret` `nret` `mode` |
| 42 | **[MODE_PROCEDURE](#mode-procedure)** | procedure call | `nill` `call` `fcal` `zcal` `pcal` `ncal` `mode` |
| 43 | **[MODE_PROCEDURE_TCO_RET ](#mode-procedure-tco-ret)** | procedure return with tco | `nill` `back` `fret` `zret` `pret` `nret` `mode` |

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

## MODE STRING ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | put number as binary |
| `stro` | 2 | 010 | put number as octal |
| `stri` | 3 | 011 | put number as decimal |
| `strx` | 4 | 100 | put number as hexadecimal |
| `strc` | 5 | 101 | put ascii character |

## MODE INPUT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | input number as binary |
| `stro` | 2 | 010 | input number as octal |
| `stri` | 3 | 011 | input number as decimal |
| `strx` | 4 | 100 | input number as hexadecimal |
| `strc` | 5 | 101 | input ascii character |

## MODE INPUT SILENT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | input number as binary |
| `stro` | 2 | 010 | input number as octal |
| `stri` | 3 | 011 | input number as decimal |
| `strx` | 4 | 100 | input number as hexadecimal |
| `strc` | 5 | 101 | input ascii character |

## MODE INPUT PASSWORD ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `strb` | 1 | 001 | input number as binary |
| `stro` | 2 | 010 | input number as octal |
| `stri` | 3 | 011 | input number as decimal |
| `strx` | 4 | 100 | input number as hexadecimal |
| `strc` | 5 | 101 | input ascii character |

## MODE MEMORY ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `free` | 1 | 001 | realese memory |
| `aloc` | 2 | 010 | reserve memory and set a value |
| `moff` | 3 | 011 | memory config remove mask |
| `muse` | 4 | 100 | memory config append mask |
| `mmax` | 5 | 101 | set max value allowed in memory |
| `mmin` | 6 | 110 | set min value allowed in memory |

## MODE MEMORY PTR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `free` | 1 | 001 | realese memory in pointer |
| `aloc` | 2 | 010 | set a value in pointer |
| `pull` | 3 | 011 | pull aux memory to address pointer memory (ptr <- aux) |
| `spin` | 4 | 100 | inverse values inner memory pointer and aux (ptr <-> aux) |
| `push` | 5 | 101 | push aux memory to pointer memory (ptr -> aux) |


## MODE MEMORY AUX ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `free` | 1 | 001 | realese memory aux |
| `aloc` | 2 | 010 | set a value in aux memory |
| `pull` | 3 | 011 | pull aux memory to address memory (addr <- aux) |
| `spin` | 4 | 100 | inverse values inner memory and aux (addr <-> aux) |
| `push` | 5 | 101 | push aux memory to address memory (addr -> aux) |

## MODE JUMP ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `goto` | 1 | 001 | jump to the label unconditionally |
| `fgto` | 2 | 010 | jump to the label if aux memory is fill |
| `zgto` | 3 | 011 | jump to the label if aux memory is empty |
| `pgto` | 4 | 100 | jump to the label if aux memory is positive |
| `ngto` | 5 | 101 | jump to the label if aux memory is negative |

## MODE MATH SUM ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | add value in the aux memory |

## MODE MATH SUB ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | subtraction in the aux memory |

## MODE MATH MUL ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | multiplication in the aux memory |

## MODE MATH DIV ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | division in the aux memory |

## MODE MATH MOD ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | rest of the division with aux memory |

## MODE MATH POWER ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | enhance aux memory value |


## MODE MATH ROOT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | root aux memory value |

## MODE MATH ABS ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | module positive aux memory value |

## MODE MATH NEGATIVE ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | negative module aux memory value |


## MODE HELPER AVERAGE ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | avarange values received and storage in the aux memory |

## MODE HELPER SIGN ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | verify number sign and storage in aux memory (-1, 0, 1) |

## MODE HELPER MAX ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | keep higher number in auxiliary memory |

## MODE HELPER MIN ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | keep less number in aux memory |


## MODE HELPER PERCENTAGE ##

| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | percentage aux memory value |

## MODE HELPER REVERSE ##

| name | octal | bit | description |
| ------ | - | --- | - |
| `nb02` | 1 | 001 | base 2 reverse number |
| `nb08` | 1 | 010 | base 8 reverse number |
| `nb10` | 1 | 011 | base 10 reverse number |
| `nb16` | 1 | 100 | base 16 reverse number |

## MODE HELPER LOG BASE 2 ##

| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | base 2 logarithm |

## MODE HELPER LOG BASE 10 ##

| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | base 10 logarithm |

## MODE HELPER MUL ADD ##

| name | octal | bit | description |
| ------ | - | --- | - |
| `nb02` | 1 | 001 | multiply by 2 and accumulate operation |
| `nb08` | 2 | 010 | multiply by 8 and accumulate operation |
| `nb10` | 3 | 011 | multiply by 10 and accumulate operation |
| `nb16` | 4 | 100 | multiply by 16 and accumulate operation |

## MODE BOOL NOT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean not |

* **truth table**

| aux | !aux |
| :-: | :-: |
| 0 | 1 |
| 1 | 0 |

## MODE BOOL AND ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean and |

* **truth table**

| aux | math | aux * math |
| :-: | :--: | :--------: |
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

## MODE BOOL OR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean or |

* **truth table**

| aux | math | aux + math |
| :-: | :--: | :--------: |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

## MODE BOOL XOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean xor |

* **truth table**

| aux | math | aux (+) math |
| :-: | :--: | :----------: |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

## MODE BOOL NAND ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean nand |

* **truth table**

| aux | math | !(aux * math) |
| :-: | :--: | :-----------: |
| 0 | 0 | 1 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

## MODE BOOL NOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean nor |

* **truth table**

| aux | math | !(aux + math) |
| :-: | :--: | :-----------: |
| 0 | 0 | 1 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 0 |

## MODE BOOL XNOR ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean xnor |

* **truth table**

| aux | math | !(aux (+) math) |
| :-: | :--: | :-----------: |
| 0 | 0 | 1 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

## MODE BOOL AND NOT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean and not |

* **truth table**

| aux | math | aux * !math |
| :-: | :--: | :--------: |
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

## MODE BOOL OR NOT ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `math` | 1 | 001 | boolean or not |

* **truth table**

| aux | math | aux + !math |
| :-: | :--: | :--------: |
| 0 | 0 | 1 |
| 0 | 1 | 0 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

## MODE PROCEDURE_RET ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `call` | 1 | 001 | return from procedure unconditionally |
| `fcal` | 2 | 010 | return from procedure if aux memory is fill |
| `zcal` | 3 | 011 | return from procedure if aux memory is empty |
| `pcal` | 4 | 100 | return from procedure if aux memory is positive |
| `ncal` | 5 | 101 | return from procedure if aux memory is negative |

## MODE PROCEDURE ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `call` | 1 | 001 | call label procedure unconditionally |
| `fcal` | 2 | 010 | call label procedure if aux memory is fill |
| `zcal` | 3 | 011 | call label procedure if aux memory is empty |
| `pcal` | 4 | 100 | call label procedure if aux memory is positive |
| `ncal` | 5 | 101 | call label procedure if aux memory is negative |

## MODE PROCEDURE_RET_TCO ##

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `call` | 1 | 001 | return from procedure at label unconditionally |
| `fcal` | 2 | 010 | return from procedure at label if aux memory is fill |
| `zcal` | 3 | 011 | return from procedure at label if aux memory is empty |
| `pcal` | 4 | 100 | return from procedure at label if aux memory is positive |
| `ncal` | 5 | 101 | return from procedure at label if aux memory is negative |

 * **NOTE**: _this cpu mode should be used for **Tail Call Optimization**, or else to make explicit when procedures will be terminated passing a label._
