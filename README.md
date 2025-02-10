# Long Integer Library

## Overview
The **longintlib** is a lightweight dynamic arbitrary-precision arithmetic library providing basic functions for operating long integers. Syntax is pretty straightforward making it simple and highly customisible. This project consists of the library itself, tests and examples.

A brief introduction is provided below. See [documentation](https://github.com/l8stwisd8m/longintlib/blob/main/docs/Documentation.md) in the `docs` folder for more detailed types & functions description.

## Quick start
You can download a headers & precompiled dynamic library file in the **Releases** (currently, for Linux users only - if you're running MacOS or Windows, you have to change the target platform in the `Makefile` and build shared library file (.dylib or .dll) with `make`).

The `longintlib.h`contains all the necessary prototypes and type definitions. The header can be included manually; to compile a file you need to link it with one of the following shared objects:

• `liblongint.so` for Linux;

• `liblongint.dll` for Windows;

• `liblongint.dylib` for MacOS.

To run any tests or examples `git clone` this project and build executables:

`make -f MakefileTest` for tests;

`make -f MakefileExample` for examples.

Default `Makefile` is intended for compiling shared object file, so it can be modified and executed with `make` command to recompile it when necessary.

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
**Warning**: value array lenght must always corresond to the `size` value and be greater than zero. There are no assertions or `size` checks in library functions.

**Note**: avoid using different sized variables. Arguments of certain functions, such as `div` and `mod`, must the same size.

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

There are plenty useful constants and macros in `longintconst` and `longintmacro` headers. See `docs` folder for more detailed explanation.

## Issues, contributing etc.

Feel free to fork and modify the project! You can contribute anything to the `dev` branch. Good examples will be added to the main branch; however, the amount of source files is limited to reasonable limits to keep the library less bloated.

I would also appreciate recieving suggestions for improving any features, found bugs, patches, etc - open an [issue](https://github.com/l8stwisd8m/longintlib/issues) to submit it. Please, provide bug reports detailed information how to reproduce it.
