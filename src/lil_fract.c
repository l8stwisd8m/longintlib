#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"
#include <inttypes.h>

int lil_fract(double *dst, lil_t *src_a, lil_t *src_b) {
    // fraction produced by division of a by b
    
    // default result
    *dst = 0;
    
    // exceptions
    if (lil_is_null(src_a)) return 0; // a = 0 => a / b = 0
    
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_b)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; division can not be performed");
        exit(EXIT_FAILURE); // invalid b value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    // most significant digits
    uint64_t msd_a = 0;
    uint64_t msd_b = 0;
    
    uint64_t len_a = lil_len(src_a);
    uint64_t len_b = lil_len(src_b);
    int shift = 0;
    
    if (len_a <= LIL_BASE) msd_a = src_a->val[0];
    else {
        for (size_t i = src_a->size - 1; i > 0; i--) {
            if (src_a->val[i]) {
                shift = __builtin_ctzll(src_a->val[i]);
                msd_a = (src_a->val[i] << shift) | (src_a->val[i - 1] >> (LIL_BASE - shift));
            }
        }
    }
    
    if (len_b <= LIL_BASE) msd_b = src_b->val[0];
    else {
        for (size_t i = src_b->size - 1; i > 0; i--) {
            if (src_b->val[i]) {
                shift = __builtin_ctzll(src_b->val[i]);
                msd_b = (src_b->val[i] << shift) | (src_b->val[i - 1] >> (LIL_BASE - shift));
            }
        }
    }
    
    printf("MSD a:\t%"PRIx64"\n", msd_a);
    printf("MSD b:\t%"PRIx64"\n", msd_b);
    *dst = (double)msd_a / (double)msd_b;
    
    return 0;
}
