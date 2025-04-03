#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

int lil_val_mod(lil_t *src_a, lil_t *src_m) {
    // update a so it belongs to the range from zero to m
    
    // exceptions
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; value can not be updated");
        exit(EXIT_FAILURE); // invalid b value
    }
    if (src_a->size != src_m->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; value can not be updated");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    
    long_int *tmp;
    LIL_MALLOC(tmp, src_a->size);
    
    // a < 0 => a += m
    if (src_a->sign == LIL_MINUS) {
        if (lil_cmp_val(src_a, src_m) != 1) {
            // abs(a) <= abs(b)
            lil_sum(tmp, src_a, src_m);
            lil_cpy(src_a, tmp); // a <- a + m
        }
        else {
            // abs(a) > abs(b)
            LIL_CPY_VAL(tmp, src_a);
            lil_mod(src_a, tmp, src_m); 
            LIL_CPY_VAL(tmp, src_a); // a <- a % m
            src_m->sign = LIL_MINUS;
            lil_sum(src_a, tmp, src_m); // a <- a - m
            src_m->sign = LIL_PLUS;
            src_a->sign = LIL_PLUS; // a <- (-a)
        }
    }
    
    // a > m => a <- a % m
    if (lil_cmp_val(src_m, src_a) != 1) {
        LIL_CPY_VAL(tmp, src_a);
        lil_mod(src_a, tmp, src_m); // a <- a % m
    }
    
    LIL_FREE(tmp);
    return 0;
}
