### COMMON ###
| name | octal | bit |
| ------ | - | --- |
| `nill` | 0 | 000 | skip line (null) |
| `mode` | 7 | 111 | change cpu register bank |

### MEMORY `mode: 0` ###
| name | octal | bit | description |
| `free` | 1 | 001 | realese memory |
| `aloc` | 2 | 010 | reserve memory and set a value |
| `copy` | 3 | 011 | clone value from another address |

### STRING `mode: 1` ### 
| name | octal | bit | description |
| `stri` | 1 | 001 | put literal number |
| `strc` | 2 | 010 | put ascii character |
| `stro` | 3 | 011 | put literal number in octal |
| `strx` | 4 | 100 | put literal number in hexadecimal |
