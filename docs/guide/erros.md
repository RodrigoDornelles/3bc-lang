---
title: Errors
description: all error codes, description and how to resolve them.
---

| Code | Description | Solution |
| :--: | :---------- | :------- |
| | UNKNOWN ERROR | report the problem! [click here](https://github.com/RodrigoDornelles/3bc-lang/issues/new) |
| 0x00000B | SEGMENT FAULT | report the problem! [click here](https://github.com/RodrigoDornelles/3bc-lang/issues/new) |
| 0x3BC000 | CPU MODE IS NOT DEFINED | You need to set a CPU mode to use any register |
| 0x3BC001 | CPU MODE IS RESERVED | Custom register has been added or has another opcode |
| 0x3BC002 | INVALID CPU REGISTER | Enter a valid value in the first column |
| 0x3BC003 | INVALID CPU ADDRESS | Enter a valid value in the second column |
| 0x3BC004 | INVALID CPU CONSTANT | Enter a valid value in the thirdy column |
| 0x3BC005 | INVALID CPU MODE | Check cpu mode [click here](https://3bc-lang.org/guide/cheatsheet) |
| 0x3BC006 | INVALID LABEL | Repeat markup, conflict with a hash literal or an unexpected negative number. |
| 0x3BC007 | INVALID PROCEDURE RETURN | Check if you are calling procedures and returning correctly. |
| 0x3BC008 | DUALITY ADDRES WITH VALUE IS NOT ALLOWED | Use only an address or a constant. |
| 0x3BC009 | VALUE OR ADDRESS IS REQUIRE | Important use some constant value or address. |
| 0x3BC00A | VALUE IS REQUIRED | Set a constant value. |
| 0x3BC00B | ADDRESS IS REQUIRED | Set a memory address. |
| 0x3BC00C | VALUE IS NOT ALLOWED | Unexpected constant value. | 
| 0x3BC00D | ADDRESS IS NOT ALLOWED | Not expected a memory address. |
| 0x3BC00E | NUMBER WHIOUT DIGITS | Missing numeric digits. |
| 0x3BC00F | NUMBER UNDERFLOW | Unexpected number because the value is too small. |
| 0x3BC010 | NUMBER OVERFLOW | Unexpected number because the value is too large. |
| 0x3BC011 | NUMBER WRONG BASE | Digit does not match number base |
| 0x3BC012 | NUMBER NEGATIVE IS NOT EXPECTED | Mem. Aux, Mem. Main or constant has a negative irregular number. |
| 0x3BC013 | NUMBER ZERO IS NOT EXPECTED | An irregular null value found. (example: divide by zero) |
| 0x3BC014 | OUT OF MEMORY | Check for stack or buffer overflow. |
| 0x3BC015 | NONE TTY | To use a teleprompter you must define the input or output. |
| 0x3BC016 | UNSUPPORTED FEATURE | This feature is not supported by the architecture. |
| 0x3BC017 | MEMORY CONFIG | Resolving conflicts in memory usage. |
| 0x3BC018 | CANNOT OPEN FILE | File does not exist, or system does not have permission. |
| 0x3BC019 | NULL POINTER | Point to a valid memory address. |
| 0x3BC01A | INVALID CHARACTER ESCAPE | Control character not supported by the language. |
| 0x3BC01B | INVALID CHARACTER SIZE | Control character not supported by the language. |
| 0x3BC01C | WRONG NUMBER OF COLUMNS | Every row must strictly have 3 columns. |
