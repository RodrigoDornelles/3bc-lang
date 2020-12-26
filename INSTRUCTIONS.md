## COMMON ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `nill` | 0 | 000 | label reference point or skip line (null) |
| `mode` | 7 | 111 | change cpu register bank |

## NO MODE `mode: 0` `DONT USE` ##

## DEBUG `mode: 1` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `stri` | 1 | 001 | log literal number |
| `strc` | 2 | 010 | log ascii character |
| `stro` | 3 | 011 | log literal number in octal |
| `strx` | 4 | 100 | log literal number in hexadecimal |
| `stru` | 5 | 101 | log literal number (unsigned) |

## STRING `mode: 2` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `stri` | 1 | 001 | put literal number |
| `strc` | 2 | 010 | put ascii character |
| `stro` | 3 | 011 | put literal number in octal |
| `strx` | 4 | 100 | put literal number in hexadecimal |
| `stru` | 5 | 101 | put literal number (unsigned) |

## INPUT `mode: 3` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `stri` | 1 | 001 | input literal number |
| `strc` | 2 | 010 | input ascii character |
| `stro` | 3 | 011 | input literal number in octal |
| `strx` | 4 | 100 | input literal number in hexadecimal |

## INPUT SILENT `mode: 4` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `stri` | 1 | 001 | input literal number |
| `strc` | 2 | 010 | input ascii character |
| `stro` | 3 | 011 | input literal number in octal |
| `strx` | 4 | 100 | input literal number in hexadecimal |

## INPUT PASSWORD `mode: 5` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `stri` | 1 | 001 | input literal number |
| `strc` | 2 | 010 | input ascii character |
| `stro` | 3 | 011 | input literal number in octal |
| `strx` | 4 | 100 | input literal number in hexadecimal |

## MEMORY `mode: 6` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `free` | 1 | 001 | realese memory |
| `aloc` | 2 | 010 | reserve memory and set a value |
| `smin` | 4 | 011 | set memory min value possible |
| `srev` | 3 | 100 | set memory reversable |
| `smax` | 5 | 101 | set memory max value possible |

## PROTECTED `mode: 7` `DONT USE` ##

## MEMORY AUX `mode: 8` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `free` | 1 | 001 | realese memory aux |
| `aloc` | 2 | 010 | set a value in aux memory |
| `pull` | 3 | 011 | pull aux memory to address memory (addr <- aux) |
| `push` | 4 | 100 | push aux memory to address memory (addr -> aux) |

## JUMP `mode: 9` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `goto` | 1 | 001 | jump to the label unconditionally |
| `fgto` | 2 | 010 | jump to the label if aux memory is fill |
| `zgto` | 3 | 011 | jump to the label if aux memory is empty |
| `pgto` | 4 | 100 | jump to the label if aux memory is positive |
| `ngto` | 5 | 101 | jump to the label if aux memory is negative |

## --- `mode: 10` ##
reserved for future memory bank function

## MATH SUM `mode: 11` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | add value in the aux memory |

## MATH SUB `mode: 12` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | subtraction in the aux memory |

## MATH MULTI `mode: 13` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | multiplication in the aux memory |

## MATH DIV `mode: 14` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | division in the aux memory |

## MATH MOD `mode: 15` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | rest of the division with aux memory |

## MATH POWER `mode: 16` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | enhance aux memory value |


## MATH ROOT `mode: 17` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | root aux memory value |

## MATH PERCENTAGE `mode: 18` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | percentage aux memory value |

## MATH ABS `mode: 19` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | module positive aux memory value |

## MATH AVERAGE `mode: 20` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `math` | 1 | 001 | avarange values received and storage in the aux memory |