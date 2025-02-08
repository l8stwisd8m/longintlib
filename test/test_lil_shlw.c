#include <stdio.h>
#include <stdint.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"

void test_shlw(lil_t *a) {
    printf("a:\t");
    lil_print_hex(a);
    lil_shlw(a);
    printf("a << 1:\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // bitwise left shift by word size test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Left shift by word size test \n");
    
    printf("Shift of an empty value \n");
    test_shlw(&a);
    
    printf("Most significant digit is not null \n");
    a.val[N - 1] = 0x1234567;
    test_shlw(&a);
    
    printf("Least significant digit is not null \n");
    a.val[N - 1] = 0;
    a.val[0] = 0x1234567;
    test_shlw(&a);
    
    printf("All digits are \"full\" \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    test_shlw(&a);
    
    return 0;
}
