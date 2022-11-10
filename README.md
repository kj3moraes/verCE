[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
# verCE

A language frontend with LLVM pronounced like the word '_verse_'. This language has almost python-like syntax with a few tidbits from C/C++. The compiler currently supports :

* `double` type variables
* Binary operations
* Function calls and definitions
* `extern` keyword
* JIT compilation

More features will be added soon. Refer to `docs/LANGUAGE_DOC.md` for information on how to use the language, what is supported and how to get started.

## Building and Experimenting

To build the program, just type `make all` when you are in the root directory. This will create /bin and /build directories. The executable will be in the /bin directory. The requirements are :

* clang>=8.0
* LLVM>=3.6
* GNU Make

To rebuild completely again, type

```bash
make remake
```

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
