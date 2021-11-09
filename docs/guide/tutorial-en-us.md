Tutorial in English :🇺🇸:
==============================

3BC is a low-level, easy-to-learn programming language that works in the form of a virtual machine similar to a 1960s computer, but with a very unusual architecture that has processors of only **3 bits**.

Despite having an aspect to be an esoteric language, it has a good capacity for generic use to solve computational problems, and certain advantages with the implementation in embedded and microcontrollers.

It was introduced by a Brazilian at Christmas 2020 after completing a month of development, being a project for studies and also as a conceptual proof of concept about punched cards being readable and practical for both humans and machines.

How to make a "Hello world!"
--------------------------

These steps will guide you through running the hello world example and getting your first 3BC program running on your machine, so let's get started.

After downloading the binary from _[donwload](https://3bc-lang.org/download)_, simply unzip the file and use the command line to run the source code using the interpreter according to your operating system: **windows**, **mac os**, **unix** or **linux**.


 * **Examples:** `helloworld.3bc`

```RUBY
MODE NILL 0d2
STRC NILL 'o'
STRC NILL 'l'
STRC NILL 'a'
STRC NILL ' '
STRC NILL 'm'
STRC NILL 'u'
STRC NILL 'n'
STRC NILL 'd'
STRC NILL 'o'
STRC NILL '!'
```

 * **windows**

using 'terminal' or 'cmd' type:

```
C:\Users\nicod\Downloads\3bc-windows-32> 3bc.exe helloworld.3bc
hello world!
C:\Users\nicod\Downloads\3bc-windows-32>
```

 * **mac** / **unix** / **linux**

using the shell of your choice type:

```
$ ./3bc helloworld.3bc
hello world!
$
```

Structure
---------

A great point to facilitate the learning, is its very well organized syntax of the language. With a quick view separated in rows and columns, where these have a fixed size of parameters, even when not used.

A program line is consequently an instruction, which has three mandatory parameters. They are separated in the respectively order of **register**, **address**, **constant**.

![structure_en><](https://3bc-lang.org/images/structure-en-us.png)

 * **Register**

The register defines the behavior of the instruction be it printing to the screen, capturing inputs, summing, etc. 

You should use mnemonics like `mode`, `math` and `nill` or some literal expressions that represent its opcode from 0 to 7. Be guided by the _[cheatsheet](https://3bc-lang.org/cheatsheet)_ guide, which explains in detail about each instruction.

Depending on the register it is necessary to pass or not **address** and **constant** values. It can be either mandatory or restrictive, or not accept both in the same instruction, to avoid ambiguity.


 * **Address**

Address is a space in memory used to store certain data, some instruction sets depend on it.

You must use a literal expression. It is important to note that using _hash_ such as :my_variable in small programs is fine, but monolithic structures can have conflicts between addresses.

 * **Constant**

Constant would be a fixed, unchanging value.

Syntax
-------

### Literal Expressions ###

There is no typing in the language, just raw data; For ease of use, the interpreter accepts several representations of these values, such as:

| Description | Representation |
| :-------- | ------------: |
| Caracter ASCII | `'Z'` |
| Positive decimal | `9` `0d9` `0i9` |
| Negative decimal | `-9` `-0d9` `-0i9` | 
| Octal positive/negative | `0o7` `-0o7` |
| Binary positive/negative | `0b1` `-0b1` | 
| HexaDecimal positive/negative | `0xF` `-0xF` |
| Hash Generator | `:minha_funcao` |
| Zero or Null | `0` `0d0` `0i0` `0o0` `0b0` `0x0` `'\0'` `NILL` |


### Tags ###

Known as _labels_ are markings in the program where conditional jumps or procedure calls can happen, no label can be re-labeled. It is possible to make jumps in any direction of the algorithm.

 * **Making markings**

When both the **register** and **address** columns have null values, any constant value will be considered a bookmark.

```RUBY
NILL NILL 0x01
```

 * **Tagging Tip**

The [literal-expression](#literary-expressions) _hash_ generator is intended to make it easier to organize the _labels_ in your code, so as not to rely on just numeric markup.

```RUBY
NILL NILL :loop start
```

* **Example**

```RUBY
MODE NILL 0d8
GOTO NILL :entry # Jump to the entry point

MODE NILL 0d2
STRC NILL 'h' # Not run
STRC NILL 'i' # Not run
STRC NILL ' ' # Not run
STRC NILL ' ' # Not run
NILL NILL :entry
STRC NILL 'f' # run
STRC NILL 'r' # run
STRC NILL 'i' # run
STRC NILL 'e' # run
STRC NILL 'n' # run
STRC NILL 'd' # run
```

Expected Outcome:

```
friend
```

## Paradigms ##

## Unstructured ##

The unstructured paradigm can be used for several occasions such as elaborating selection and condition deviations, making repetition loops, and even a complete program fast and efficient. But its overuse can bring great maintenance difficulties and unexpected behavior.

* **MODE:** 0d9

| name | octal | bit | description |
| :--: | :---: | :-: | :---------- |
| `goto` | 1 | 001 | jump to the label unconditionally |
| `fgto` | 2 | 010 | jump to the label if the auxiliary memory is full |
| `zgto` | 3 | 011 | jump to the label if the auxiliary memory is empty |
| `pgto` | 4 | 100 | jump to the label if the auxiliary memory is positive |
| `ngto` | 5 | 101 | jump to the label if the auxiliary memory is negative |

#### Repeating loops ####

* **Infinite**

Print 'cafe' uninterruptedly. 

```RUBY
MODE NILL 0d2
NILL NILL :loop
STRX NILL 0xCAFE
MODE NILL 0d9
GOTO NILL :loop
```

* **Print while**


Print '...' using _of_ _while_.

```RUBY
# Value of :var is 3
MODE NILL 0d6
ALOC :var 0d3

# Print '.'
MODE NILL 0d02
NILL NILL :do_while
STRC NILL '.'

# Add -1 in :var
MODE NILL 0d8
PUSH :var NILL
MODE NILL 0d11
MATH NILL -1
MODE 0 0d08
PULL :var 0

# Repeat as long as var: is not equal to 0
MODE NILL 0d9
FGTO NILL :do_while
```

* **While**

Print '...' using _while_.

```RUBY
# Valor of :var is 3
MODE NILL 0d6 
ALOC :var 3

# While :var is not equal to 0
MODE NILL 0d8
NILL NILL :where_entry
PUSH :var NILL
MODE NILL 0d9
ZGTO NILL :where_exit

# Print '.'
MODE NILL 0d2
STRC NILL '.'

# Subtract 1 from :var
MODE NILL 0d8
PUSH :var NILL
MODE NILL 0d12
MATH NILL 1
MODE NILL 0d8
PULL :var NILL

# End of while
MODE NILL 0d9
GOTO NILL :where_entry
NILL NILL :where_exit
```

#### Conditional Deviation ###

 * **If Different**

Print '!=' if the input is different from 5.

```RUBY
# Keyboard capture and store in :cmp
MODE NILL 0d4
STRI :cmp NILL

# Compare the negation (:cmp != 5)
MODE NILL 0d8
PUSH :cmp NILL
MODE NILL 0d12
MATH NILL 5
MODE NILL 0d9
ZGTO NILL :if_equal

# Print '!='
MODE NILL 0d2
STRC NILL '!'
STRC NILL '='

# End program.
NILL NILL :if_equal
```

 * **If Equal, Greater or Lesser**

Print '**n**<5' if less number is less, print '**n**=5' if number is exactly 5 or print '**n**>5' if it is greater. Where **n** will be the keyboard input.

```RUBY
# Keyboard capture and store in :cmp
MODE NILL 0d3
STRI :cmp NILL

# Compare with 5
MODE NILL 0d8
PUSH :cmp NILL
MODE NILL 0d12
MATH NILL 5
MODE NILL 0d9
NGTO NILL :if_less
ZGTO NILL :if_equal
PGTO NILL :if_greater

# Print '<'
MODE NILL 0d2
NILL NILL :if_less
STRC NILL '<'
MODE NILL 0d9
GOTO NILL :if_exit

# Print '='
MODE NILL 0d2
NILL NILL :if_equal
STRC NILL '='
MODE NILL 0d9
GOTO NILL :if_exit

# Print '>'
MODE NILL 0d2
NILL NILL :if_greater
STRC NILL '>'
MODE NILL 0d9
GOTO NILL :if_exit

# Print '5'
MODE NILL 0d2
NILL NILL :if_exit
STRI NILL 5
```

### Procedural ##

The procedural paradigm (popularly called procedural), has the advantage of making a stack of processes, where there is a return point at the same place as its call. This can make it easier to write large programs.

```RUBY
# Jump to entry point
MODE NILL 0d9
GOTO NILL :entry

# Procedure :print_bar
MODE NILL 0d2
NILL NILL :print_bar # Label
STRC NILL 'B'
STRC NILL 'a'
STRC NILL 'r'
MODE NILL 0d41 # Return Mode
BACK NILL NILL # Return unconditionally

# Procedure :print_foo
MODE NILL 0d2
NILL NILL :print_foo # Start of the process
STRC NILL 'F'
STRC NILL 'o'
STRC NILL 'o'
MODE NILL 0d41 
BACK NILL NILL # End of process

# Entry point
MODE NILL 0d42   # Call procedures and return
NILL NILL :entry # Entry point
CALL NILL :print_foo # Call :print_foo
CALL NILL :print_bar # Call :print_bar
```
