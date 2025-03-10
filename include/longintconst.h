#ifndef _LONG_INT_CONST_
#define _LONG_INT_CONST_

// sign 
#define LIL_PLUS 0
#define LIL_MINUS 1

// size
#define LIL_128_BIT 2U
#define LIL_256_BIT 4U
#define LIL_512_BIT 8U
#define LIL_1024_BIT 16U
#define LIL_2048_BIT 32U
#define LIL_4096_BIT 64U

// bitmasks
#define LIL_RH 0x00000000ffffffffULL
#define LIL_LH 0xffffffff00000000ULL
#define LIL_MSBIT 0x8000000000000000ULL
#define LIL_LSBIT 0x0000000000000001ULL
#define LIL_MSBYTE 0x8000000000000000ULL
#define LIL_LSBYTE 0x00000000000000fULL

// utils
enum lil_util {
    LIL_BASE = 64,
    LIL_SPLIT = 32
};

// errors 
enum lil_error {
    LIL_NO_ERROR,
    LIL_OVERFLOW,
    LIL_TRUNCATED
};

#endif // _LONG_INT_CONST_
