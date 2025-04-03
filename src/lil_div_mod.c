#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

int lil_div_mod(lil_t *dst, lil_t *src_a, lil_t *src_b, lil_t *src_m) {
    // multiplication of a and inverted b modulo m
    
    // exceptions
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; multiplication can not be performed");
        exit(EXIT_FAILURE); // invalid b value
    }
    if ((src_a->size != dst->size) or (src_m->size != dst->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; multiplication can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    
    lil_val_mod(src_a, src_m); // a <- a mod m
    lil_print_dec(src_a);
    long_int *tmp_b;
    LIL_MALLOC(tmp_b, src_b->size);
    lil_inv(tmp_b, src_b, src_m); // b <- inv(b)
    lil_print_dec(tmp_b);
    lil_mul_mod(dst, src_a, tmp_b, src_m); // a * b mod m
    
    return 0;
}
