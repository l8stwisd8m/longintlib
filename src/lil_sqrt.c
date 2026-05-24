#include <errno.h>
#include <stdio.h>
#include <iso646.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_sqrt(lil_t *dst, lil_t *src) {
    // floor from square root of source
    
    // default result
    LIL_SET_NULL(dst);
    
    // exceptions
    if (lil_is_null(src)) return 0; // sqrt(0) = 0
    
    #ifdef LIL_INVALID_INPUT 
    if (src->sign == LIL_MINUS) {
        errno = ERR_INVALID_INPUT;
        perror("Square root of a negative number can not be found; square root calculation can not be performed");
        exit(EXIT_FAILURE); // invalid input
    }
    #endif /* LIL_INVALID_INPUT */
    
    long_int *tmp;
    LIL_MALLOC(tmp, src->size);
    
    dst->val[0] = 1;
    uint64_t shift = lil_len(src);
    shift = shift % 2 == 0 ? shift / 2: shift / 2 + 1;
    lil_shln(dst, shift);
    
    while(1) {
        lil_div(tmp, src, dst);
        lil_add(tmp, dst);
        lil_shr(tmp);
        if (lil_cmp_val(tmp, dst) != -1) {
            LIL_FREE(tmp);
            return 0;
        }
        LIL_CPY_VAL(dst, tmp);
    }
    
    LIL_FREE(tmp);
    return 0;
}
