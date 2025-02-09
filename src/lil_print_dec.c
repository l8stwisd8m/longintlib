#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
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
    
    // memory allocation for temporary structures
    long_int *digit = (long_int *)malloc(sizeof(long_int));
    long_int *value = (long_int *)malloc(sizeof(long_int));
    long_int *base = (long_int *)malloc(sizeof(long_int));
    long_int *tmp = (long_int *)malloc(sizeof(long_int));
    assert(digit and value and base and tmp);
    digit->size = src->size; base->size = src->size;
    value->size = src->size; tmp->size = src->size;
    digit->val = (uint64_t *)malloc(src->size * sizeof(uint64_t));
    value->val = (uint64_t *)malloc(src->size * sizeof(uint64_t));
    base->val = (uint64_t *)calloc(src->size, sizeof(uint64_t));
    tmp->val = (uint64_t *)malloc(src->size * sizeof(uint64_t));
    assert(digit->val and value->val and base->val and tmp->val);
    
    for (int i = 0; i < src->size; i++) {
        value->val[i] = src->val[i]; // value = src
    }
    base->val[0] = 10; // base = 10
    
    // left shift base while base < value
    while(lil_cmp_val(base, value) != 1) {
        lil_short_mul(base, 10);
    }
    // correct base (div by 10)
    lil_cpy(tmp, base); // tmp = base
    lil_short_div(base, tmp, 10); // base = tmp / 10
    
    // digits calculation
    while(lil_is_null(value) != 1) {
        lil_div(digit, value, base); // digit = floor(value/base)
        printf("%"PRIu64, digit->val[0]);
        lil_cpy(tmp, base);
        lil_short_mul(tmp, digit->val[0]);
        lil_sub(value, tmp); // value -= base * floor(value/base)
        lil_cpy(tmp, base);
        lil_short_div(base, tmp, 10); // base /= 10
    }

    free(digit->val); free(digit);
    free(value->val); free(value);
    free(base->val); free(base);
    free(tmp->val); free(tmp);

    #ifdef NEW_LINE
    putchar('\n');
    #endif /* ifdef NEW_LINE */
}
