#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_val_mod(lil_t *src_a, lil_t *src_m) {
    // update a so it belongs to the range from zero to m
    
    // exceptions
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; value can not be updated");
        exit(EXIT_FAILURE); // invalid m value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if (src_a->size != src_m->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; value can not be updated");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES */
    
    // a = 0 => a mod m = 0
    if (lil_is_null(src_a)) {
        src_a->sign = LIL_PLUS;
        return 0; 
    }
    
    int cmp_flag = lil_cmp_val(src_a, src_m);
    
    // a = m => a mod m = 0
    if (cmp_flag == 0) {
        src_a->sign = LIL_PLUS;
        LIL_SET_NULL(src_a);
        return 0; 
    }
    
    long_int *tmp;
    LIL_MALLOC(tmp, src_a->size);
    
    // a < 0, abs(a) <= abs(b) => a <- (m + a)
    if ((src_a->sign == LIL_MINUS) and (cmp_flag == -1)) {
        lil_sum(tmp, src_a, src_m);
        lil_cpy(src_a, tmp); // a <- a + m
        src_a->sign = LIL_PLUS;
        LIL_FREE(tmp);
        return 0;
    }
    
    // a < 0, abs(a) > abs(b) => a <- (m + a) mod m
    if ((src_a->sign == LIL_MINUS) and (cmp_flag == 1)) {
        tmp->sign = LIL_PLUS;
        LIL_CPY_VAL(tmp, src_a);
        lil_mod(src_a, tmp, src_m); // a <- abs(a) % m
        LIL_CPY_VAL(tmp, src_a);
        src_m->sign = LIL_MINUS;
        lil_sum(src_a, tmp, src_m); // a <- a - m
        src_m->sign = LIL_PLUS;
        src_a->sign = LIL_PLUS; // a <- abs(a)
        LIL_FREE(tmp);
        return 0;
    }
    
    // a > m => a <- a mod m
    if (cmp_flag == 1) {
        LIL_CPY_VAL(tmp, src_a);
        lil_mod(src_a, tmp, src_m); // a <- a % m
    }
    
    LIL_FREE(tmp);
    return 0;
}
