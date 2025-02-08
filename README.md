# Long Integer Library

## Overview
The **longintlib** is a lightweight dynamic arbitrary-precision arithmetic library providing basic functions for operating long integers. Syntax is pretty straightforward making it simple and highly customisible. This project consists of the library itself, tests and examples.

A brief introduction is provided below. See `docs` for more detailed types & functions description.

## Quick start
You can download a header & precompiled dynamic library files in the **Releases** section. 
The `longintlib.h`contains all the necessary prototypes and type definitions. The header can be included manually; to compile a file you need to link it with one of the following shared objects:
• `liblongintlib.so` for Linux;
• `liblongintlib.dll` for Windows;
• `liblongintlib.dylib` for MacOS.

To run any tests or examples `git clone` this project and build executables:
`make -f MakefileTest` for tests;
`make -f MakefileExample` for examples.
Default `Makefile` is intended for compiling .so file, so it can be modified and executed with `make` command to recompile it.

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
Each `val` array element represents a single digit of the value. Functions treat `val` arrays as little-endian numbers, so you should input numbers in reversed order or use `lil_rev` to change the order of a value. The only exceptions are `print` functions, which print numbers in direct order.
**Note**: value array lenght should always corresond to the `size` value and be greater than zero. There are no assertions or `size` checks in library functions.

Here's recommended way of initializing a warriable:
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