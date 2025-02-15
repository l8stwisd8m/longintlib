# Documentation

## Table of contents 

### [Introduction](#introduction-1)

### [Long Integer type](#long-integer-type-1)

### [Constants](#constants-1)
1. [Sign constants](#1-sign-constants)  
2. [Size constants](#2-size-constants)  
3. [Bitmasks & other practical constants](#3-bitmasks--other-practical-constants)

### [Macros](#macros-1)
1. [Copy value (LIL_CPY_VAL)](#1-copy-value-lil_cpy_val) 
2. [Set null (LIL_SET_NULL)](#2-set-null-lil_set_null) 
3. [Memory allocation (LIL_MALLOC)](#3-memory-allocation-lil_malloc) 
4. [Clean memory allocation (LIL_CALLOC)](#4-clean-memory-allocation-lil_calloc) 
5. [Free memory (LIL_FREE)](#5-free-memory-lil_free) 
6. [Bitwise exclusive or (LIL_XOR)](#6-bitwise-exclusive-or-lil_xor) 
7. [Bitwise inversion (LIL_NOT)](#7-bitwise-inversion-lil_not)
8. [Bitwise conjunction (LIL_AND)](#8-bitwise-conjunction-lil_and) 
9. [Bitwise disjunction (LIL_OR)](#9-bitwise-disjunction-lil_or)

### [Basic functions](#basic-functions-1)
1. [Reverse value (lil_rev)](#1-reverse-value-lil_rev)
2. [Copy value (lil_cpy)](#2-copy-value-lil_cpy)
3. [Length of value (lil_len)](#3-length-of-value-lil_len)
4. [Compare values (lil_cmp)](#4-compare-values-lil_cmp)
5. [Compare lengths (lil_cmp_len)](#5-compare-lengths-lil_cmp_len)
6. [Compare absolute values (lil_cmp_val)](#6-compare-absolute-values-lil_cmp_val)
7. [Check if null (lil_is_null)](#7-check-if-null-lil_is_null)
8. [Check if even (lil_is_even)](#8-check-if-even-lil_is_even)
9. [Check if odd (lil_is_odd)](#9-check-if-odd-lil_is_odd)

### [Print & Scan functions](#print--scan-functions-1)
1. [Print binary (lil_print_bin)](#1-print-binary-lil_print_bin)
2. [Print decimal(lil_print_dec)](#2-print-decimal-lil_print_dec)
3. [Print hexadecimal(lil_print_hex)](#3-print-hexadecimal-lil_print_hex)
4. [Scan binary (lil_scan_bin)](#4-scan-binary-lil_scan_bin)
5. [Scan decimal(lil_scan_dec)](#5-scan-decimal-lil_scan_dec)
6. [Scan hexadecimal(lil_scan_hex)](#6-scan-hexadecimal-lil_scan_hex)

### [Basic math functions](#basic-math-functions-1)
1. [Addition (lil_add)](#1-addition-lil_add)
2. [Subtraction (lil_sub)](#2-subtraction-lil_sub)
3. [Arithmetic sum (lil_sum)](#3-arithmetic-sum-lil_sum)
4. [Multiplication (lil_mul)](#4-multiplication-lil_mul)
5. [Division (lil_div)](#5-division-lil_div)
6. [Modulus (lil_mod)](#6-modulus-lil_mod)
7. [Greatest Common Divisor (lil_gcd)](#7-greatest-common-divisor-lil_gcd)

### [Unary math functions](#unary-math-functions-1)
1. [Increment value (lil_inc)](#1-increment-value-lil_inc)
2. [Decrement value (lil_dec)](#2-decrement-value-lil_dec)

### [Shifts](#shifts-1)
1. [Left shift (lil_shl)](#1-left-shift-lil_shl)
2. [Right shift (lil_shr)](#2-right-shift-lil_shr)
3. [Left shift by word size (lil_shlw)](#3-left-shift-by-word-size-lil_shlw)
4. [Right shift by word size (lil_shrw)](#4-right-shift-by-word-size-lil_shrw)
5. [Left shift by n bits (lil_shln)](#5-left-shift-by-n-bits-lil_shln)
6. [Right shift by n bits (lil_shrn)](#6-right-shift-by-n-bits-lil_shrn)

### [Short operations](#short-operations-1)
1. [Short addition (lil_short_add)](#1-short-addition-lil_short_add)  
2. [Short subtraction (lil_short_sub)](#2-short-subtraction-lil_short_sub)  
3. [Short multiplication (lil_short_mul)](#3-short-multiplication-lil_short_mul)  
4. [Short division (lil_short_div)](#4-short-division-lil_short_div)  
5. [Short modulo (lil_short_mod)](#5-short-modulo-lil_short_mod)  
6. [Short power modulo (lil_short_pow_mod)](#6-short-power-modulo-lil_short_pow_mod)

### [Custom functions](#custom-functions-1)
1. [Fast GCD (lil_fast_gcd)](#1-fast-gcd-lil_fast_gcd)

## Introduction 
The **longintlib** is a lightweight dynamic arbitrary-precision arithmetic library providing basic functions for operating long integers. Syntax is pretty straightforward making it simple and highly customisible. This project consists of the library itself, tests and examples.

There are three **headers**:

• `longintlib.h` containing custom type called `lil_t` or `long_int` and prototypes of [functions](#basic-functions-1);

• `longintconst.h` for often used [constants](#constants-1), such as variables sizes, bit masks and other;

• `longintmacro.h` for useful function-like [macros](#macros-1).

Here's brief description of functions, provided by **longintlib**:

1. **Basic functions** — these functions manipulate the data structure `long_int` and provide fundamental operations such as reversing the order of values, copying structures, and comparing values or lengths. They help manage `long_int` instances by determining length, checking for emptiness, and identifying even or odd values.
2. **Print and scan functions** — this set of functions is responsible for outputting and inputting the data in various numeral systems: binary, decimal, and hexadecimal. They facilitate visualization of the `lil_t` content and allow for user input in multiple formats, enhancing user interaction with the library.
3. **Basic math functions** — these functions perform essential arithmetic operations on `lil_t` data, including addition, subtraction, multiplication, division, and modulo, providing a mathematical foundation for working with the long integer representations.
4. **Unary math functions** — these functions offer simple incremental and decremental operations on the `lil_t` structure, enabling easy adjustment of values by one unit, which is essential for iterative algorithms and value adjustments.
5. **Shifts** — the shift functions allow for bitwise shifting operations on the `lil_t` values, enabling both left and right shifts by one bit or by word size, as well as by a specified number of bits. These operations are vital for efficient data manipulation at a binary level.
6. **Modular arithmetic functions** — this category handles operations in modular arithmetic, such as multiplication and exponentiation modulo a given number. They are beneficial for cryptographic computations and other scenarios requiring modular constraints. **Currently unavailable**.
7. **Short operations** — these functions perform arithmetic operations involving both `lil_t` values and short integer values (consisting of a single digit, `uint64_t` number). They allow for efficient calculations and manipulations with smaller integer values, useful in various applications where long integers interact with standard integers for performance and memory efficiency.

The `longintlib.h` header contains some [custom functions](#custom-functions-1), which are located in the `custom` folder to keep the main source files folder and the library itself less bloated. These files provide additional functional, however, some of them can not be tested proprerly. To use any of these functions, you need to move corresponding source file from `custom` to `src` directory and recompile shared object with `make` command.

## Long Integer type 
The library provides one main **type** called `lil_t` or :

```
typedef struct {
    enum {PLUS, MINUS} sign;
    uint64_t *val;
    size_t size;
} lil_t;
```

The `long_int` definition is a pseudonym for `lil_t` type for more readability.

An array for value storing should be allocated before variable initialization.

The `sign` value can be left uninitialized (most of the functions doesn't use it).
**Note**: enumerations `PLUS` and `MINUS` can be used only while initialization (inside braces); constants `LIL_PLUS` and `LIL_MINUS` from `longintconst.h` may be used instead.

Each `val` array element represents a single digit of the value. Functions treat `val` arrays as little-endian numbers, so you have to input numbers in reversed order or use `lil_rev` to change the order of a value. The only exceptions are `scan` functions, which expect numbers to be entered in direct order.
**Warning**: value array lenght must always corresond to the `size` value and be greater than zero. There are no assertions or `size` checks in library functions.

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

There are `LIL_MALLOC`, `LIL_CALLOC` and `LIL_FREE` [macros](#macros-1) which can be used when you need to allocate space for value storage and have size of the value only without need to initialize a sign or value itself. For instance:
```
const int n = 8;
lil_t *var;
LIL_MALLOC(var, n);
/* ... */
LIL_FREE(var);
```
The `LIL_CALLOC` macro can be used the same way.

## Constants 
The `longintconst.h` header file defines key constants crucial for managing long integers effectively. This includes `Sign` constants that help determine the positivity or negativity of values, `Size` constants that specify the maximum and minimum limits of long integers, and various `Bitmasks` used for effective data manipulation.

### 1. Sign constants
The sign constants are used to represent basic arithmetic signs of variables. The enumerations `PLUS` and `MINUS`, used in `lil_t` type definition, are undefined to avoid conflicts with eponymous constants from other libraries, so they can be used only inside variable initializations. To change the sign of a variable, one can use `0` for *plus* and `1` for *minus*, or the following constants:

1. **LIL_PLUS**: Represents the positive sign.
2. **LIL_MINUS**: Represents the negative sign.

### 2. Size constants
Size constants define various bit sizes used in memory allocation. Each constant represent the amount of digits used to store a number of certain bit length.

1. **LIL_128_BIT**: Represents a data size of 128 bits.
2. **LIL_256_BIT**: Represents a data size of 256 bits.
3. **LIL_512_BIT**: Represents a data size of 512 bits.
4. **LIL_1024_BIT**: Represents a data size of 1024 bits.
5. **LIL_2048_BIT**: Represents a data size of 2048 bits.
6. **LIL_4096_BIT**: Represents a data size of 4096 bits.

Here's an example of using a size constant:
```
lil_t *var;
LIL_MALLOC(var, LIL_256_BIT);
```

### 3. Bitmasks & other practical constants
These constants are critical for bitwise operations and data manipulation. They help in isolating specific bits or bytes from data structures.

1. **LIL_BASE**: Represents bit length of a single digit number.
2. **LIL_SPLIT**: Represents half bit length of a single digit numbers.
3. **LIL_RH**: Mask for the right half of a 64-bit value.
4. **LIL_LH**: Mask for the left half of a 64-bit value.
5. **LIL_MSBIT**: Represents the most significant bit in a 64-bit integer.
6. **LIL_LSBIT**: Represents the least significant bit in a 64-bit integer.
7. **LIL_MSBYTE**: Represents the most significant byte in a 64-bit integer.
8. **LIL_LSBYTE**: Represents the least significant byte in a 64-bit integer.

## Macros
The `longintmacro.h` header file contains a collection of macros designed to simplify and streamline operations with long integers. Among these macros, you'll find utilities for copying values, setting source values to null, and allocating memory efficiently. Additionally, it includes various bitwise operation macros for performing AND, OR, NOT and XOR operations seamlessly. 

### 1. Copy value (LIL_CPY_VAL)
*Macro copies the source value to the destination value.*  
Input arguments are pointers to the long_int destination and source (lil_t *DST and lil_t *SRC).  
Result is stored in the destination argument - source "DST" (DST).  

### 2. Set null (LIL_SET_NULL)
*Macro sets the source value to null.*  
Input argument is a pointer to the long_int source (lil_t *SRC).  
Result is stored in the source argument - source "SRC" (SRC).  
**Note**: there is a similar macro called 'LIL_STATIC_SET_NULL' which performs the sama action, but it's input argument is long_int (not a pointer).

### 3. Memory allocation (LIL_MALLOC)
*Macro allocates memory for the source.*  
Input arguments are a pointer to the long_int source pointer and the size (long_int **SRC and size_t SIZE).  
Result is stored in the source pointer argument - source pointer "SRC" (SRC).  

### 4. Clean memory allocation (LIL_CALLOC)
*Macro performs a clean memory allocation for the source.*  
Input arguments are a pointer to the long_int source pointer and the size (long_int **SRC and size_t SIZE).  
Result is stored in the source pointer argument - source pointer "SRC" (SRC).  

### 5. Free memory (LIL_FREE)
*Macro frees the memory allocated for the source.*  
Input argument is a pointer to the long_int source pointer (lil_t *SRC).  
Result is that the memory associated with the source argument "SRC" is freed.  

### 6. Bitwise exclusive or (LIL_XOR)
*Macro performs a bitwise exclusive or operation.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *SRC_A and lil_t *SRC_B).  
Result is stored in the first argument - source "a" (SRC_A).  

### 7. Bitwise inversion (LIL_NOT)
*Macro performs a bitwise inversion operation.*
Input argument is pointer to the `long_int` source "src" (lil_t *SRC).
Result is stored in the source argument - source pointer "SRC" (SRC).

### 8. Bitwise conjunction (LIL_AND)
*Macro performs a bitwise conjunction operation.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *SRC_A and lil_t *SRC_B).  
Result is stored in the first argument - source "a" (SRC_A).  

### 9. Bitwise disjunction (LIL_OR)
*Macro performs a bitwise disjunction operation.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *SRC_A and lil_t *SRC_B).  
Result is stored in the first argument - source "a" (SRC_A).

## Basic functions

### 1. Reverse value (lil_rev)
*Function reverses source value.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is stored in the source variable (src).  

### 2. Copy value (lil_cpy)
*Function copies source structure to destination.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *dst and lil_t *src).  
Result is stored in the destination variable (dst).  

### 3. Length of value (lil_len)
*Function returns bit length of source.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is the bit length of the source.  

### 4. Compare values (lil_cmp)
*Function compares two values.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is 0 if a = b, -1 if a < b, 1 if a > b.  

### 5. Compare lengths (lil_cmp_len)
*Function compares the lengths of two values.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is 0 if length(a) = length(b), -1 if length(a) < length(b), 1 if length(a) > length(b).  

### 6. Compare absolute values (lil_cmp_val)
*Function compares the absolute values of two sources.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is 0 if abs(a) = abs(b), -1 if abs(a) < abs(b), 1 if abs(a) > abs(b).  

### 7. Check if null (lil_is_null)
*Function checks if the source is empty.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is 1 if source is empty, 0 otherwise.  

### 8. Check if even (lil_is_even)
*Function checks if the source is even.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is 1 if source is even, 0 otherwise.  

### 9. Check if odd (lil_is_odd)
*Function checks if the source is odd.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is 1 if source is odd, 0 otherwise.  

## Print & Scan functions

### 1. Print binary (lil_print_bin)
*Function prints the binary representation of the source.*  
Input argument is a pointer to the long_int source (lil_t *src).  
**Note**: output format is customisible — sign, prefix and separator between digits can be modified in the source file. 

### 2. Print decimal (lil_print_dec)
*Function prints the decimal representation of the source.*  
Input argument is a pointer to the long_int source (lil_t *src).
**Note**: output format is customisible — sign can be modified in the source file.

### 3. Print hexadecimal (lil_print_hex)
*Function prints the hexadecimal representation of the source.*  
Input argument is a pointer to the long_int source (lil_t *src).  
**Note**: output format is customisible — sign, prefix and separator between digits can be modified in the source file.

### 4. Scan binary (lil_scan_bin)
*Function scans and inputs a binary representation into the source.*  
Input argument is a pointer to the long_int source (lil_t *src).  
**Note**: the source value should have enough lenght to store a number. Excess input will be truncated.

### 5. Scan decimal (lil_scan_dec)
*Function scans and inputs a decimal representation into the source.*  
Input argument is a pointer to the long_int source (lil_t *src).  
**Note**: the source value should have enough lenght to store a number. Excess input will be truncated.

### 6. Scan hexadecimal (lil_scan_hex)
*Function scans and inputs a hexadecimal representation into the source.*  
Input argument is a pointer to the long_int source (lil_t *src).
**Note**: the source value should have enough lenght to store a number. Excess input will be truncated.

## Basic math functions

### 1. Addition (lil_add)
*Function adds two values together.*
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is stored in the first argument - source "a" (src_a).  

### 2. Subtraction (lil_sub)
*Function subtracts b from a.*
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is stored in the first argument - source "a" (src_a).

### 3. Arithmetic sum (lil_sum)
*Function calculates the arithmetic sum of two values*
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).  

### 4. Multiplication (lil_mul)
*Function performs multiplication of two values.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lilt *dst).  
Result is stored in the destination variable (dst).  
**Warning**: the destination variable size can not be less than the sum of source term sizes.

### 5. Division (lil_div)
*Function calculates the floor from the division of a by b.*
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).  
**Warning**: function arguments must be of the same length.

### 6. Modulus (lil_mod)
*Function calculates the remainder after division of a by b.*
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).
**Warning**: function arguments must be of the same length.

### 7. Greatest Common Divisor (lil_gcd)
*Function calculates the greatest common divisor of a by b.*
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).
**Warning**: function arguments must be of the same length.

## Unary math functions

### 1. Increment value (lil_inc)
*Function increments the source value.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is stored in the source variable (src).  

### 2. Decrement value (lil_dec)
Function decrements the source value.  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is stored in the source variable (src).  

## Shifts

### 1. Left shift (lil_shl)
*Function performs a left shift by one bit.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is stored in the source variable (src).  

### 2. Right shift (lil_shr)
*Function performs a right shift by one bit.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is stored in the source variable (src).  

### 3. Left shift by word size (lil_shlw)
*Function performs a left shift by word size.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is stored in the source variable (src).  

### 4. Right shift by word size (lil_shrw)
*Function performs a right shift by word size.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is stored in the source variable (src).  

### 5. Left shift by n bits (lil_shln)
*Function performs a left shift by n bits.*  
Input arguments are a pointer to the long_int source (lil_t *src) and the number of bits to shift (uint64_t n).  
Result is stored in the source variable (src).  

### 6. Right shift by n bits (lil_shrn)
*Function performs a right shift by n bits.*  
Input arguments are a pointer to the long_int source (lil_t *src) and the number of bits to shift (uint64_t n).  
Result is stored in the source variable (src).  

### Short operations

### 1. Short addition (lil_short_add)
*Function adds a short absolute value of b to the absolute value of long a.*  
Input arguments are a pointer to the long_int source "a" (lil_t *src_a) and a short value "b" (uint64_t src_b).  
Result is stored in the first argument (src_a).  

### 2. Short subtraction (lil_short_sub)
*Function subtracts a short absolute value of b from the absolute value of long a.*  
Input arguments are a pointer to the long_int source "a" (lil_t *src_a) and a short value "b" (uint64_t src_b).  
Result is stored in the first argument (src_a).  

### 3. Short multiplication (lil_short_mul)
*Function multiplies the absolute value of long a by a short absolute value of b.*  
Input arguments are a pointer to the long_int source "a" (lil_t *src_a) and a short value "b" (uint64_t src_b).  
Result is stored in the first argument (src_a).  
**Warning**: the most significant digit of source value "a" should be zero, otherwise an overflow can occur during multiplication.

### 4. Short division (lil_short_div)
*Function calculates the floor from the division of long a by a short value b.*  
Input arguments are pointers to the long_int source "a" (lil_t *src_a) and a short value "b" (uint64_t src_b), and a pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).  
**Note**: it is recommended to use `lil_div` whenever it is possible to avoid using the `lil_short_div` due to its dynamic memory consumption. 

### 5. Short modulo (lil_short_mod)
*Function calculates the short remainder after the division of long a by a short value b.*  
Input arguments are a pointer to the destination variable (uint64_t *dst), a pointer to the long_int source "a" (lil_t *src_a), and a short value "b" (uint64_t val_b).  
Result is stored in the destination variable (dst).  
**Note**: it is recommended to use `lil_div` whenever it is possible to avoid using the `lil_short_div` due to its dynamic memory consumption.
**Note**: since the remainder after the division by a single digit is also a single digit, destination variable is a *uint64_t* value.

### 6. Short power modulo (lil_short_pow_mod)
*Function raises the long a to the power of short n modulo long m.*  
Input arguments are a pointer to the long_int source "a" (lil_t *src_a), a short value "n" (uint64_t n), and a pointer to the long_int source "m" (lil_t *src_m).  
Result is stored in the first argument (src_a).  

### Custom functions

### 7. Fast GCD (lil_fast_gcd)
*Function calculates the greatest common divisor of a by b.*
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).
**Warning**: function arguments must be of the same length.
**Warning**: currently, the function doesn't work properly when the most significant digits of both terms are not zeroes due to the overflow, so the values should have some extra length.
