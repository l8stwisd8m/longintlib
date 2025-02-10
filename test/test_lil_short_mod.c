#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#include "test_utils.h"

void test_short_mod(lil_t *a, uint64_t b, uint64_t c) {
    PRINT_ARG(a);
    printf("b:\t0x %"PRIx64"\n", b);
    c = lil_short_mod(a, b);
    printf("a %% b:\t0x %"PRIx64"\n", c);
}

int main(int argc, char *argv[]) {
    // short modulus test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    uint64_t b = 0x1234567;
    uint64_t c = 0;
    
    printf("Short modulus calculation test \n");
    
    printf("Modulus of a term equal to zero and a non-zero value \n");
    test_short_mod(&a, b, c);
    
    printf("Modulus of two equal terms \n");
    a.val[0] = 0x1234567;
    test_short_mod(&a, b, c);
    
    printf("Modulus of two unequal terms \n");
    a.val[0] = 0x1234321;
    test_short_mod(&a, b, c);
    
    printf("Modulus of two unequal terms \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    test_short_mod(&a, b, c);
    
    printf("Invalid modulus \n");
    b = 0;
    test_short_mod(&a, b, c);
    
    return 0;
}
