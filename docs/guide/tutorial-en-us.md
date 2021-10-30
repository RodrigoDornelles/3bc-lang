Tutorial
--------

## How to "Hello World" ##

These steps will guide you to run the hello world example and to have your first 3BC program running in your machine, let get's started.

After downloading the binary on the [releases](https://github.com/RodrigoDornelles/3bc-lang/releases) page, just decompress the file and utilize the command line to interpret the source code using the compiler according to your operating system: **windows**, **mac os**, **unix** and **linux**.

### example: `helloworld.3bc` ###

```RUBY
mode nill 0d2
strc nill 'h'
strc nill 'e'
strc nill 'l'
strc nill 'l'
strc nill 'o'
strc nill ' '
strc nill 'w'
strc nill 'o'
strc nill 'r'
strc nill 'l'
strc nill 'd'
strc nill '!'
```

### windows ###

```
C:\Users\nicod\Downloads\3bc-windows-32> 3bc.exe helloworld.3bc
hello world!
C:\Users\nicod\Downloads\3bc-windows-32>
```

### mac / unix / linux ###

```
$ ./3bc helloworld.3bc
hello world!
$
```