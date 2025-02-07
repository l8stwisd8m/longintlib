# Documentation

## Table of contents 

### Basic functions
1. [Reverse value (lil_rev)](#reverse-value-(lil_rev)-1)
2. [Copy value (lil_cpy)](#copy-value-(lil_cpy)-2)
3. [Length of value (lil_len)](#length-of-value-(lil_len)-3)
4. [Compare values (lil_cmp)](#compare-values-(lil_cmp)-4)
5. [Compare lengths (lil_cmp_len)](#compare-lengths-(lil_cmp_len)-5)
6. [Compare absolute values (lil_cmp_val)](#compare-absolute-values-(lil_cmp_val)-6)
7. [Check if null (lil_is_null)](#check-if-null-(lil_is_null)-7)
8. [Check if even (lil_is_even)](#check-if-even(lil_is_even)-8)
9. [Check if odd (lil_is_odd)](#check-if-odd(lil_is_odd)-9)

### Print & Scan functions
1. [Print binary (lil_print_bin)](#print-binary-(lil_print_bin)-1)
2. [Print hexadecimal(lil_print_hex)](#print-hexadecimal-(lil_print_hex)-2)

### Shifts
1. [Left shift (lil_shl)](#left-shift-(lil_shl)-1)
2. [Right shift (lil_shr)](#right-shift(lil_shr)-2)
3. [Left shift by word size (lil_shlw)](#left-shift-by-word-size-(lil_shlw)-3)
4. [Right shift by word size (lil_shrw)](#right-shift-by-word-size-(lil_shrw)-4)
5. [Left shift by n bits (lil_shln)](#left-shift-by-n-bits(lil_shln)-5)
6. [Right shift by n bits (lil_shrn)](#right-shift-by-n-bits(lil_shrn)-6)

### Bitwise operations
1. [Bitwise exclusive or (lil_xor)](#bitwise-exclusive-or-(lil_xor)-1)
2. [Bitwise conjunction (lil_and)](#bitwise-conjunction-(lil_and)-2)

### Unary math functions
1. [Increment value (lil_inc)](#increment-value-(lil_inc)-1)
2. [Decrement value (lil_dec)](#decrement-value-(lil_dec)-2)

### Basic math functions
1. [Addition (lil_add)](#addition-(lil_add)-1)
2. [Subtraction (lil_sub)](#subtraction-(lil_sub)-2)
3. [Arithmetic sum (lil_sum)](#arithmetic-sum-(lil_sum)-3)
4. [Multiplication (lil_mul)](#multiplication-(lil_mul)-4)
5. [Division (lil_div)](#division-(lil_div)-5)
6. [Modulus (lil_mod)](#modulus-(lil_mod)-6)

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

### 2. Print hexadecimal (lil_print_hex)
*Function prints the hexadecimal representation of the source.*  
Input argument is a pointer to the long_int source (lil_t *src).  

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
Input arguments are pointers to the long_int sources "a" and "b" (lil_t src_a and lil_t src_b).  
Result is stored in the first argument - source "a" (src_a).  

## Unary math functions

### 1. Increment value (lil_inc)
*Function increments the source value.*  
Input argument is a pointer to the long_int source (lil_t *src).  
Result is stored in the source variable (src).  

### 2. Decrement value (lil_dec)
Function decrements the source value.  
Input argument is a pointer to the long_int source (lil_t src).  
Result is stored in the source variable (src).  

## Basic math functions

### 1. Addition (lil_add)
Function adds two values together.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t src_a and lil_t src_b).  
Result is stored in the first argument - source "a" (src_a).  

### 2. Subtraction (lil_sub)
Function subtracts b from a.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t src_a and lil_t src_b).  
Result is stored in the first argument - source "a" (src_a).  

### 3. Arithmetic sum (lil_sum)
Function calculates the arithmetic sum of two values.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t src_a and lil_t src_b) and pointer to the destination variable (lil_t dst).  
Result is stored in the destination variable (dst).  

### 4. Multiplication (lilmul)
*Function performs multiplication of two values.*  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t *src_a and lil_t *src_b) and pointer to the destination variable (lilt *dst).  
Result is stored in the destination variable (dst).  

### 5. Division (lil_div)
Function calculates the floor from the division of a by b.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t src_a and lil_t src_b) and pointer to the destination variable (lil_t dst).  
Result is stored in the destination variable (dst).  

### 6. Modulus (lil_mod)
Function calculates the remainder after division of a by b.  
Input arguments are pointers to the long_int sources "a" and "b" (lil_t src_a and lil_t src_b) and pointer to the destination variable (lil_t dst).  
Result is stored in the destination variable (dst).
