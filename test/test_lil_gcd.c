#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "test_utils.h"

void test_gcd(lil_t *a, lil_t *b, lil_t *c) {
    PRINT_ARG(a);
    PRINT_ARG(b);
    lil_gcd(c, a, b);
    printf("gcd:\t");
    lil_print_hex(c);
}

int main(int argc, char *argv[]) {
    // gcd test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    uint64_t arr_c[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    long_int c = {PLUS, arr_c, N};
    
    printf("Greatest common divisor calculation test \n");
    
    printf("GCD of a term equal to zero and a non-zero value \n");
    b.val[0] = 0x01234567;
    test_gcd(&a, &b, &c);
    
    printf("GCD of two equal terms of same size \n");
    a.val[1] = BASE_MAX; a.val[0] = 0xfedcba9876543210;
    b.val[1] = BASE_MAX; b.val[0] = 0xfedcba9876543210;
    test_gcd(&a, &b, &c);
    
    printf("GCD of two unequal terms \n");
    a.val[2] = BASE_MAX; b.val[0] = 0x1234567; b.val[1] = 0;
    test_gcd(&a, &b, &c);
    
    printf("GCD of two unequal terms \n");
    a.val[2] = BASE_MAX; b.val[1] = BASE_MAX; b.val[0] = 0xfedcba9876543210;
    test_gcd(&a, &b, &c);
    
    printf("GCD of invalid terms both equal to zero \n");
    for (int i = 0; i < N; i++) {
        a.val[i] = 0; b.val[i] = 0;
    }
    test_gcd(&a, &b, &c);
    
    return 0;
}
