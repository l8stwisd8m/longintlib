#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#include "test_utils.h"

void test_short_div(lil_t *a, uint64_t b, lil_t *c) {
    PRINT_ARG(a);
    printf("b:\t0x %"PRIx64"\n", b);
    lil_short_div(c, a, b);
    printf("a / b:\t");
    lil_print_hex(c);
}

int main(int argc, char *argv[]) {
    // short divition test
    uint64_t arr_a[N] = {0};
    uint64_t arr_c[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int c = {PLUS, arr_c, N};
    uint64_t b = 0x1234567;
    
    printf("Short division test \n");
    
    printf("Division of a term equal to zero and a non-zero value \n");
    test_short_div(&a, b, &c);
    
    printf("Division of two equal terms \n");
    a.val[0] = 0x1234567;
    test_short_div(&a, b, &c);
    
    printf("Division of two unequal terms \n");
    a.val[0] = 0x1234321;
    test_short_div(&a, b, &c);
    
    printf("Division of two unequal terms \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    test_short_div(&a, b, &c);
    
    printf("Invalid division \n");
    b = 0;
    test_short_div(&a, b, &c);
    
    return 0;
}
