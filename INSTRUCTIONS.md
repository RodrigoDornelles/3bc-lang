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

## STRING `mode: 2` ##
| name | octal | bit | description |
| ------ | - | --- | - |
| `stri` | 1 | 001 | put literal number |
| `strc` | 2 | 010 | put ascii character |
| `stro` | 3 | 011 | put literal number in octal |
| `strx` | 4 | 100 | put literal number in hexadecimal |

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
| `copy` | 3 | 011 | clone value from another address |
| `getm` | 4 | 100 | get memory size |
| `setm` | 5 | 101 | set memory size |

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