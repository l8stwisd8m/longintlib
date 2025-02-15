#ifndef _LONG_INT_CONST_
#define _LONG_INT_CONST_

// sign 
#define LIL_PLUS 0
#define LIL_MINUS 1

// size
#define LIL_128_BIT 2
#define LIL_256_BIT 4
#define LIL_512_BIT 8
#define LIL_1024_BIT 16
#define LIL_2048_BIT 32
#define LIL_4096_BIT 64

// bitmasks etc.
#define LIL_BASE 64
#define LIL_SPLIT 32
#define LIL_RH 0x00000000ffffffff
#define LIL_LH 0xffffffff00000000
#define LIL_MSBIT 0x8000000000000000
#define LIL_LSBIT 0x0000000000000001
#define LIL_MSBYTE 0xff00000000000000
#define LIL_LSBYTE 0x00000000000000ff

#endif // _LONG_INT_CONST_
