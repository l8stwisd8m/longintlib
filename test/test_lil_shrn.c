#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"

void shrn(lil_t *a, uint64_t n) {
    printf("Shift by n = %"PRIu64" bits\n", n);
    lil_shrn(a, n);
    printf("a >> n:\t");
    lil_print_hex(a);
}

void test_shrn(lil_t *a) {
    printf("a:\t");
    lil_print_hex(a);
    shrn(a, 0);
    shrn(a, 16);
    shrn(a, 48);
    shrn(a, 32);
}

int main(int argc, char *argv[]) {
    // bitwise right shift by n bits test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Right shift by n bits test \n");
    
    printf("Shift of an empty value \n");
    test_shrn(&a);
    
    printf("Most significant digit is not null \n");
    a.val[N - 1] = 0x12345678abcd;
    test_shrn(&a);
    
    printf("Least significant digit is not null \n");
    a.val[N - 3] = 0; a.val[N - 2] = 0;
    a.val[0] = 0x12345678abcd;
    test_shrn(&a);
    
    printf("All digits are \"full\" \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    test_shrn(&a);
    
    return 0;
}
