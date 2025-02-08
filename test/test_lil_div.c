#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"

void test_div(lil_t *a, lil_t *b, lil_t *c) {
    print_args(a, b);
    lil_div(c, a, b);
    printf("a / b:\t");
    lil_print_hex(c);
}

int main(int argc, char *argv[]) {
    // division test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    uint64_t arr_c[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    long_int c = {PLUS, arr_c, N};
    
    printf("Division test \n");
    
    printf("Division of a term equal to zero and a non-zero value \n");
    b.val[0] = 0x01234567;
    test_div(&a, &b, &c);
    
    printf("Division of two equal terms of same size \n");
    a.val[1] = BASE_MAX; a.val[0] = 0xfedcba9876543210;
    b.val[1] = BASE_MAX; b.val[0] = 0xfedcba9876543210;
    test_div(&a, &b, &c);
    
    printf("Division of two equal terms of same size \n");
    a.val[2] = BASE_MAX; b.val[0] = 0x1234567; b.val[1] = 0;
    test_div(&a, &b, &c);
    
    printf("Invalid division of different sized terms \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)malloc(b.size * sizeof(uint64_t));
    b.val = new_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_div(&a, &b, &c);
    
    free(new_arr_b);
    return 0;
}
