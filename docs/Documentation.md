# Documentation

## Table of contents 

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

### [Basic math functions](#basic-math-functions-1)
1. [Addition (lil_add)](#1-addition-lil_add)
2. [Subtraction (lil_sub)](#2-subtraction-lil_sub)
3. [Arithmetic sum (lil_sum)](#3-arithmetic-sum-lil_sum)
4. [Multiplication (lil_mul)](#4-multiplication-lil_mul)
5. [Division (lil_div)](#5-division-lil_div)
6. [Modulus (lil_mod)](#6-modulus-lil_mod)

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

### [Bitwise operations](#bitwise-operations-1)
1. [Bitwise exclusive or (lil_xor)](#1-bitwise-exclusive-or-lil_xor)
2. [Bitwise conjunction (lil_and)](#2-bitwise-conjunction-lil_and)

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

### 2. Print decimal (lil_print_dec)
*Function prints the decimal representation of the source.*  
Input argument is a pointer to the long_int source (lil_t *src).  

### 3. Print hexadecimal (lil_print_hex)
*Function prints the hexadecimal representation of the source.*  
Input argument is a pointer to the long_int source (lil_t *src).  

## Basic math functions

### 1. Addition (lil_add)
Function adds two values together.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is stored in the first argument - source "a" (src_a).  

### 2. Subtraction (lil_sub)
Function subtracts b from a.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is stored in the first argument - source "a" (src_a).  

### 3. Arithmetic sum (lil_sum)
Function calculates the arithmetic sum of two values.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).  

### 4. Multiplication (lil_mul)
*Function performs multiplication of two values.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lilt *dst).  
Result is stored in the destination variable (dst).  

### 5. Division (lil_div)
Function calculates the floor from the division of a by b.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).  

### 6. Modulus (lil_mod)
Function calculates the remainder after division of a by b.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lil_t *dst).  
Result is stored in the destination variable (dst).

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

## Bitwise operations

### 1. Bitwise exclusive or (lil_xor)
*Function performs a bitwise exclusive or operation.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is stored in the first argument - source "a" (src_a).  

### 2. Bitwise conjunction (lil_and)
*Function performs a bitwise conjunction operation.*
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b).  
Result is stored in the first argument - source "a" (src_a).  
