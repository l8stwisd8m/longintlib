# Long Integer Library

[![docs](https://img.shields.io/badge/docs-blue)](https://github.com/l8stwisd8m/longintlib/blob/main/docs/Documentation.md)
![release - v0.1](https://img.shields.io/badge/release-v0.1-blueviolet)
![coverage - 94.8%](https://img.shields.io/badge/coverage-94.8%-violet)

## Overview

The **𝖑𝖔𝖓𝖌𝖎𝖓𝖙𝖑𝖎𝖇** is a lightweight dynamic arbitrary-precision arithmetic library for x86-64 providing basic functions for operating long integers. Syntax is pretty straightforward making it simple and highly customizable. This project consists of the library itself, tests and examples.  
There are also additional features, not included in the main library file, but which can be added separately.

A brief introduction is provided below. See [documentation](https://github.com/l8stwisd8m/longintlib/blob/main/docs/Documentation.md) for more detailed types & functions description.

**Requirments**:  

• `GCC` and `Make` to compile the library;  
• [`Criterion`](https://github.com/Snaipe/Criterion) is used for unit tests [optional];  
• [`LCOV/GCOV`](https://github.com/linux-test-project/lcov) for coverage info [optional].  

## Quick start

You can download a headers & precompiled dynamic library file in the [releases](https://github.com/l8stwisd8m/longintlib/releases) (currently, for Linux users only — if you're running MacOS or Windows, you have to change the target platform in the `Makefile` and build shared library file with `make`).

The `longintlib.h`contains all the necessary prototypes and type definitions. The header can be included manually; to compile a file you need to link it with one of the following shared objects:  

• `liblongint.so` for Linux;  
• `liblongint.dll` for Windows;  
• `liblongint.dylib` for MacOS.  

To run any tests or examples `git clone` this project and build executables:  

• `make tests` for tests;  
• `make examples` for examples.  

Default `Makefile` target is intended for compiling shared object file, so it can be modified and executed with `make` command to recompile the library when necessary.  
There are various additional functions, all of which can be used to update library with `made dev`.

## Usage

The library provides one basic type called `lil_t` or `long_int`:

```
typedef struct {
    enum {PLUS, MINUS} sign;
    uint64_t *val;
    size_t size;
} lil_t;
```

An array for value storing should be allocated before variable initialization.

The `sign` value can be left uninitialized (most of the functions doesn't use it).  
**Note**: enumerations `PLUS` and `MINUS` can be used only while initialization (inside braces); constants `LIL_PLUS` and `LIL_MINUS` from `longintconst.h` may be used instead.

Each `val` array element represents a single digit of the value. Functions treat `val` arrays as little-endian numbers, so you have to input numbers in reversed order or use `lil_rev` to change the order of a value. The only exceptions are `scan` functions, which expect numbers to be entered in direct order.  
**Warning**: value array length must always corresond to the `size` value and be greater than zero. There are no assertions or `size` checks in library functions.

**Note**: avoid using different sized variables. Arguments of certain functions, such as `div` and `mod`, must have the same size.

Here's recommended way of initializing a variable:

1. Initialize a length variable;
2. Allocate an array of length defined before for value storage;
3. Initialize a `lil_t` variable with `size` equal to the array size and array pointer assigned to the `val`.

Static array value allocation example:

```
#define N 8
uint64_t values[N] = {0};
lil_t var = {PLUS, values, N};
```

Dynamic array value allocation example:

```
const int n = 8;
uint64_t *values = (uint64_t *)malloc(n * sizeof(uint64_t));
lil_t var = {PLUS, values, n};
/* ... */
free(values);
```

There are plenty useful constants and macros in `longintconst` and `longintmacro` headers. See `docs` folder for explanation.

By the way, you can copy a `template` or expolore some examples, located in the `example`. Run `make examples` to build them.

## Issues, contributing etc.

Feel free to fork and modify the project! You can contribute anything to the `main` branch. Good examples and new functions will be added to the branch; however, the amount of library functions (source files) is limited to reasonable limits to keep the library less bloated.

I would also appreciate recieving suggestions for improving any features, found bugs, patches, etc — open an [issue](https://github.com/l8stwisd8m/longintlib/issues) to submit it. Please, provide bug reports information how to reproduce it.
