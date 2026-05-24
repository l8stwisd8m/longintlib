#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"
#define MANTISSA_BITLEN 53
#define MANTISSA_BITMASK 0x0001fffffffffffff
#include <inttypes.h>

int lil_log2(double *dst, lil_t *src) {
    // logarithm of source to base 2
    
    // default result
    *dst = 0;
    
    // exceptions
    if ((src->sign == LIL_PLUS) and (lil_is_one(src))) return 0; // log2(1) = 0
    
    #ifdef LIL_INVALID_INPUT 
    if (lil_is_null(src)) {
        errno = ERR_INVALID_INPUT;
        perror("Logarithm of zero is undefined; logarithm calculation can not be performed");
        exit(EXIT_FAILURE); // invalid input
    }
    if (src->sign == LIL_MINUS) {
        errno = ERR_INVALID_INPUT;
        perror("Logarithm of a negative number can not be found; logarithm calculation can not be performed");
        exit(EXIT_FAILURE); // invalid input
    }
    #endif /* LIL_INVALID_INPUT */
    
    printf("Last digit: %"PRIx64"\n", src->val[0]);
    uint64_t len = lil_len(src);
    printf("Length:\t%"PRIu64"\n", len);
    uint64_t mask = MANTISSA_BITMASK;
    double excess = 0;
    
    for (size_t i = 0; i < LIL_BASE - MANTISSA_BITLEN; i++) {
        printf("Iteration %lu\tMask: %"PRIx64"\n", i, mask);
        printf("Log2(n):\t%f\n", log2((double)(src->val[0])));
        printf("Log2(n&mask):\t%f\n", log2((double)(src->val[0] & mask)));
        if (log2((double)(src->val[0])) == log2((double)(src->val[0] & mask))) {
            printf("Got a match here\n");
            excess = len > MANTISSA_BITLEN + i ? len - (LIL_BASE + i) : 0;
            *dst = log2((double)(src->val[0])) + excess;
            return 0;
        }
        mask = (mask << 1) | 1;
    }
    excess = len > LIL_BASE ? len - LIL_BASE : 0;
    *dst = log2((double)(src->val[0])) + excess;
    
    return 0;
}
