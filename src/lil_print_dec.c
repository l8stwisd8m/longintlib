#include <stdio.h>
#include <iso646.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"
#define NEW_LINE
#define PRINT_SIGN

void lil_print_dec(lil_t *src) {
    // print decimal representation of source
    
    #ifdef PRINT_SIGN
    if (src->sign == LIL_MINUS) putchar('-');
    #endif /* ifdef PRINT_SIGN */
    
    uint64_t value_len = lil_len(src);
    
    if (value_len <= LIL_BASE) {
        printf("%"PRIu64, src->val[0]);
        #ifdef NEW_LINE
        putchar('\n');
        #endif /* ifdef NEW_LINE */
        return; // single digit
    }
    
    // temporary structures
    long_int *digit, *value, *base, *tmp;
    LIL_MALLOC(digit, src->size);
    LIL_MALLOC(value, src->size);
    LIL_CALLOC(base, src->size);
    LIL_MALLOC(tmp, src->size);
    
    LIL_CPY_VAL(value, src); // value = src
    
    // left shift base while base < value
    base->val[0] = 10; // base = 10
    if (value_len == LIL_BASE * src->size) {
        while((LIL_MSBIT & base->val[src->size - 1]) == 0) {
            lil_short_mul(base, 10);
        }
    }
    else {
        while(lil_cmp_val(base, value) != 1) {
            lil_short_mul(base, 10);
        }
        // correct base (div by 10)
        lil_cpy(tmp, base); // tmp = base
        lil_short_div(base, tmp, 10); // base = tmp / 10
    }
    
    // digits calculation
    while(lil_is_null(base) != 1) {
        lil_div(digit, value, base); // digit = floor(value/base)
        printf("%"PRIu64, digit->val[0]); // current digit
        lil_cpy(tmp, base);
        lil_short_mul(tmp, digit->val[0]);
        lil_sub(value, tmp); // value -= base * floor(value/base)
        digit->val[0] = 10;
        lil_cpy(tmp, base);
        lil_div(base, tmp, digit); // base /= 10
    }

    LIL_FREE(digit);
    LIL_FREE(value);
    LIL_FREE(base);
    LIL_FREE(tmp);
    
    #ifdef NEW_LINE
    putchar('\n');
    #endif /* ifdef NEW_LINE */
}
