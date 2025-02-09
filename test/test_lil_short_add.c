#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "utils/test_utils.h"

void test_short_add(lil_t *a, uint64_t b) {
    short_print_args(a, b);
    lil_short_add(a, b);
    printf("a + b:\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // short addition test
    uint64_t arr_a[1] = {1};
    long_int a = {PLUS, arr_a, 1};
    uint64_t b = 1;
    
    printf("Short addition test \n");
    
    printf("Single digit value \n");
    printf("Addition without overflow \n");
    test_short_add(&a, b);
    printf("Overflow caused by addtion \n");
    a.val[0] = BASE_MAX;
    test_short_add(&a, b);
    
    a.size = 4;
    uint64_t *new_arr_a = (uint64_t *)calloc(a.size, sizeof(uint64_t));
    a.val = new_arr_a;
    b = BASE_MAX;
    
    printf("Most significant digit is not null \n");
    a.val[N - 1] = 0x1234567;
    test_short_add(&a, b);
    
    printf("Least significant digit is not null \n");
    a.val[N - 1] = 0;
    a.val[0] = 0x1234567;
    test_short_add(&a, b);
    
    printf("All digits are \"full\" \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    b = 1;
    test_short_add(&a, b);

    free(new_arr_a);
    return 0;
}
