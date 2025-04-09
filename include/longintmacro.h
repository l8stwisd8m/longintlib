#ifndef _LONG_INT_MACRO_
#define _LONG_INT_MACRO_ 

// longintlib v0.1
// https://github.com/l8stwisd8m/longintlib

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "longintlib.h"
#include "longintconst.h"

// UTILITY MACROS

// check if source value is even
#define LIL_IS_EVEN(SRC) ((SRC->val[0] & 1) == 0)

// check if source value is odd
#define LIL_IS_ODD(SRC) ((SRC->val[0] & 1) == 1)

// most significant digit
#define LIL_MSD(SRC) (SRC->val[SRC->size - 1])

// least significant digit
#define LIL_LSD(SRC) (SRC->val[0])

// set source value null
#define LIL_SET_NULL(SRC) \
    SRC->sign = LIL_PLUS; \
    for (size_t i = 0; i < SRC->size; SRC->val[i++] = 0);

// set source value positive
#define LIL_SET_PLUS(SRC) \
    SRC->sign = LIL_PLUS;

// set source value negative
#define LIL_SET_MINUS(SRC) \
    SRC->sign = LIL_MINUS;

// copy source value to destination value
#define LIL_CPY_VAL(DST, SRC) \
    do { \
        size_t _MIN_SIZE_ = (SRC->size < DST->size) ? SRC->size : DST->size; \
        for (size_t i = 0; i < _MIN_SIZE_; i++) { \
            DST->val[i] = SRC->val[i]; \
        } \
    } while(0);

// MEMORY MANAGEMENT MACROS

// memory allocation for source
#define LIL_MALLOC(SRC, SIZE) \
    SRC = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC); \
    SRC->size = SIZE; \
    SRC->sign = LIL_PLUS; \
    SRC->val = (uint64_t *)malloc((SIZE) * sizeof(uint64_t)); \
    assert(SRC->val);

// clean memory allocation for source
#define LIL_CALLOC(SRC, SIZE) \
    SRC = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC); \
    SRC->size = SIZE; \
    SRC->sign = LIL_PLUS; \
    SRC->val = (uint64_t *)calloc(SIZE, sizeof(uint64_t)); \
    assert(SRC->val);

// free memory allocated for source
#define LIL_FREE(SRC) \
    free(SRC->val); \
    free(SRC);

// memory allocation for multiple sources
#define LIL_MALLOCS(SIZE, ...) \
    do { \
        long_int* _PTRS_[] = {__VA_ARGS__}; \
        for (size_t i = 0; i < sizeof(_PTRS_) / sizeof(_PTRS_[0]); i++) { \
            LIL_MALLOC(_PTRS_[i], SIZE); \
        } \
    } while(0);

// clean memory allocation for multiple sources
#define LIL_CALLOCS(SIZE, ...) \
    do { \
        long_int* _PTRS_[] = {__VA_ARGS__}; \
        for (size_t i = 0; i < sizeof(_PTRS_) / sizeof(_PTRS_[0]); i++) { \
            LIL_CALLOC(_PTRS_[i], SIZE); \
        } \
    } while(0);

// free memory allocated for multiple sources
#define LIL_FREES(...) \
    do { \
        long_int* _PTRS_[] = {__VA_ARGS__}; \
        for (size_t i = 0; i < sizeof(_PTRS_) / sizeof(_PTRS_[0]); i++) { \
            LIL_FREE(_PTRS_[i]); \
        } \
    } while(0);

// BITWISE OPERATIONS

// bitwise exclusive or
#define LIL_BIT_XOR(SRC_A, SRC_B) \
    do { \
        size_t _MIN_SIZE_ = (SRC_A->size < SRC_B->size) ? SRC_A->size : SRC_B->size; \
        for (size_t i = 0; i < _MIN_SIZE_; i++) { \
            SRC_A->val[i] = SRC_A->val[i] ^ SRC_B->val[i]; \
        } \
    } while(0);

// bitwise inversion
#define LIL_BIT_NOT(SRC) \
    for (size_t i = 0; i < SRC->size; i++) { \
        SRC->val[i] = ~SRC->val[i]; \
    }

// bitwise conjunction
#define LIL_BIT_AND(SRC_A, SRC_B) \
    do { \
        size_t _MIN_SIZE_ = (SRC_A->size < SRC_B->size) ? SRC_A->size : SRC_B->size; \
        for (size_t i = 0; i < _MIN_SIZE_; i++) { \
            SRC_A->val[i] = SRC_A->val[i] & SRC_B->val[i]; \
        } \
    } while(0);

// bitwise disjunction
#define LIL_BIT_OR(SRC_A, SRC_B) \
    do { \
        size_t _MIN_SIZE_ = (SRC_A->size < SRC_B->size) ? SRC_A->size : SRC_B->size; \
        for (size_t i = 0; i < _MIN_SIZE_; i++) { \
            SRC_A->val[i] = SRC_A->val[i] | SRC_B->val[i]; \
        } \
    } while(0);

// DEBUG INFO DISPLAY

// print debug info (binary)
#define LIL_DEBUG_BIN(SRC) \
    printf("%s:\t", #SRC); \
    lil_print_bin(SRC);    \

// print debug info (decimal)
#define LIL_DEBUG_DEC(SRC) \
    printf("%s:\t", #SRC); \
    lil_print_dec(SRC);

// print debug info (hexadecimal)
#define LIL_DEBUG_HEX(SRC) \
    printf("%s:\t", #SRC); \
    lil_print_hex(SRC);

#endif // _LONG_INT_MACRO_
