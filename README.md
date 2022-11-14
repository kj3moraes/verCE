[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
# verCE

A language frontend with LLVM pronounced like the word '_verse_'. This language has almost python-like syntax with a few tidbits from C/C++. The compiler currently supports :

* `double` type variables
* Binary operations
* Function calls and definitions
* `extern` keyword
* Compiler optimizations like [CSE](https://en.wikipedia.org/wiki/Common_subexpression_elimination), [constant folding](https://en.wikipedia.org/wiki/Constant_folding) and propogation, etc.
* JIT compilation

More features will be added soon. Refer to `docs/LANGUAGE_DOC.md` for information on how to use the language, what is supported and how to get started.

## Building 
To build the program, just type `make all` when you are in the root directory. This will create /bin and /build directories. The executable will be in the /bin directory. The requirements are :

* clang>=8.0
* LLVM>=10.0.0
* GNU Make

To rebuild completely again, type

```bash
make remake
```

## Running
To run the verCE compiler, there are 2 modes :  
1. File Parsing
```bash
./verce <file>
```
In this mode, the compiler will read in the whole file and generate the IR for the entire file. By default optimizations are enabled in this mode. 

1. Prompt
```bash
./verce
```
In this mode, a prompt `>>` will be provided to the user where they can type in their code line-by-line. The IR will be outputed for each line entered in.

## Code Structure

The following documents the code structure of the project - what each directory does and where to find what.

```text
verCe
├── bin/
│   └── verce           : executable file
|   └── libverCE.a      : static library for verCE 
├── build/              : object/build files
├── docs/               : documentation
├── include/            : header files
│   └── AST/            : AST header files
│   └── CodeGeneration/ : IR generation header files
├── lib/                : libraries
├── src/                : source files
│   └── CodeGeneration/ : IR generation source files
├── tests/              : test files with GTEST framework
│   └── unit_tests/     : unit tests
│   └── full_tests/     : complete program tests
├── Makefile            : makefile
├── README.md           : this file

```

## References

[1] [My First Language Frontend with LLVM Tutorial](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html)  
[2] University of Waterloo CS 241 Course Notes.  
[3] [Let's write a compiler](https://briancallahan.net/blog/20210814.html)

This project is licensed under the Apache 2.0 License. See the LICENSE file for more information. The copyright notice is below.

Copyright (c) 2022 Keane Moraes
