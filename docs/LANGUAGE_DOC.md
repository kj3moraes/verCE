# verCE Language Documentation

This is the documentation for the verCE language. It contains information on how to use the language, what is supported and how to get started.

## Getting Started

This verCE language is heavily based on the Kaleidoscope language as shown in the [LLVM tutorial](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html). As it currently stands, there is no difference between the two languages. I intend to add `char` support to the languahe in the future. The following is a simple program to compute the `n^th` Fibonacci number.

```verCE
# Compute the n'th fibonacci number.
def fib(n)
  if n < 3 then
    1
  else
    fib(n-1)+fib(n-2)

# This expression will compute the 40th Fibonnaci number.
fib(40)
```

There are `extern` definitions supported as well just like in C/C++. The following is a simple example of an extern definition.

```verCE
extern user_gg 
```

