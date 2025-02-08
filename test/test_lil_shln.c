#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"

void shln(lil_t *a, uint64_t n) {
    printf("Shift by n = %"PRIu64" bits\n", n);
    lil_shln(a, n);
    printf("a << n:\t");
    lil_print_hex(a);
}

void test_shln(lil_t *a) {
    printf("a:\t");
    lil_print_hex(a);
    shln(a, 0);
    shln(a, 16);
    shln(a, 48);
    shln(a, 32);
}

int main(int argc, char *argv[]) {
    // bitwise left shift by n bits test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Left shift by n bits test \n");
    
    printf("Shift of an empty value \n");
    test_shln(&a);
    
    printf("Most significant digit is not null \n");
    a.val[N - 1] = 0x12345678abcd;
    test_shln(&a);
    
    printf("Least significant digit is not null \n");
    a.val[N - 1] = 0; 
    a.val[0] = 0x12345678abcd;
    test_shln(&a);
    
    printf("All digits are \"full\" \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    test_shln(&a);
    
    return 0;
}
