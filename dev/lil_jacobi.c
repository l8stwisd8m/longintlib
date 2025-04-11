#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintmacro.h"

int lil_jacobi(lil_t *src_a, lil_t *src_m) {
    // return 1 if a is quadratic residue modulo m, -1 if it is not, 0 if neither
    
    // exceptions
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; Jacobi symbol can not be calculated");
        exit(EXIT_FAILURE); // invalid b value
    }
    if (LIL_IS_EVEN(src_m)) {
        errno = ERR_INVALID_INPUT;
        perror("Entered modulus is not odd; Jacobi symbol can not be calculated");
        exit(EXIT_FAILURE); // invalid b value
    }
    if (src_a->size != src_m->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; Jacobi symbol can not be calculated");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    
    // correct a
    lil_val_mod(src_a, src_m);
    
    int symbol = 1;
    long_int *tmp_a, *tmp_m, *tmp;
    LIL_MALLOC(tmp, src_m->size);
    LIL_MALLOC(tmp_a, src_m->size);
    LIL_MALLOC(tmp_m, src_m->size);
    LIL_CPY_VAL(tmp_a, src_a);
    LIL_CPY_VAL(tmp_m, src_m);
    
    while(not lil_is_null(tmp_a)) {
        while(LIL_IS_EVEN(tmp_a)) {
            lil_shr(tmp_a); // a <- a / 2
            if ((LIL_LSD(tmp_m) % 8 == 3) or (LIL_LSD(tmp_m) % 8 == 5)) symbol = -symbol;
        }
        LIL_CPY_VAL(tmp, tmp_a); LIL_CPY_VAL(tmp_a, tmp_m); LIL_CPY_VAL(tmp_m, tmp); // swap a and m
        if ((LIL_LSD(tmp_a) % 4 == 3) and (LIL_LSD(tmp_m) % 4 == 3)) symbol = -symbol;
        lil_val_mod(tmp_a, tmp_m); // a <- a mod m
    }
    
    if (LIL_LSD(tmp_m) != 1) symbol = 0;
    LIL_FREES(tmp, tmp_a, tmp_m);
    return symbol;
}
