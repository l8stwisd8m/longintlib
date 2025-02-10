#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void test_mod(lil_t *a, lil_t *b, lil_t *c) {
    PRINT_ARG(a);
    PRINT_ARG(b);
    lil_mod(c, a, b);
    printf("a / b:\t");
    lil_print_hex(c);
}

int main(int argc, char *argv[]) {
    // modulus test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    uint64_t arr_c[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    long_int c = {PLUS, arr_c, N};
    
    printf("Modulus test \n");
    
    printf("Modulus of a term equal to zero and a non-zero value \n");
    b.val[0] = 0x01234567;
    test_mod(&a, &b, &c);
    
    printf("Modulus of two equal terms of same size \n");
    a.val[1] = BASE_MAX; a.val[0] = 0xfedcba9876543210;
    b.val[1] = BASE_MAX; b.val[0] = 0xfedcba9876543210;
    test_mod(&a, &b, &c);
    
    printf("Modulus of two equal terms of same size \n");
    a.val[2] = BASE_MAX; b.val[0] = 0x1234567; b.val[1] = 0;
    test_mod(&a, &b, &c);
    
    printf("Invalid modulus of different sized terms \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)malloc(b.size * sizeof(uint64_t));
    b.val = new_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_mod(&a, &b, &c);
    
    free(new_arr_b);
    return 0;
}
