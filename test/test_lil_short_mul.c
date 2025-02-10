#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "test_utils.h"

void short_print_args(lil_t *a, uint64_t b) {
    printf("a:\t");
    lil_print_hex(a);
    printf("b:\t0x %"PRIx64"\n", b);
}

void test_short_mul(lil_t *a, uint64_t b) {
    short_print_args(a, b);
    lil_short_mul(a, b);
    printf("a * b:\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // short mulition test
    uint64_t arr_a[1] = {2};
    long_int a = {PLUS, arr_a, 1};
    uint64_t b = 2;
    
    printf("Short multiplication test \n");
    
    printf("Single digit value \n");
    printf("Multiplication without overflow \n");
    test_short_mul(&a, b);
    printf("Overflow caused by multiplication \n");
    a.val[0] = 0x8000000000000000;
    test_short_mul(&a, b);
    
    a.size = 4;
    uint64_t *new_arr_a = (uint64_t *)calloc(a.size, sizeof(uint64_t));
    a.val = new_arr_a;
    b = BASE_MAX;
    
    printf("Most significant digit is not null \n");
    b = 0x1234567;
    a.val[N - 1] = 0x1234567;
    test_short_mul(&a, b);
    
    printf("Least significant digit is not null \n");
    b = BASE_MAX;
    a.val[N - 1] = 0;
    a.val[0] = 0x1234567;
    test_short_mul(&a, b);
    
    printf("All digits are \"full\" \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    test_short_mul(&a, b);

    free(new_arr_a);
    return 0;
}
