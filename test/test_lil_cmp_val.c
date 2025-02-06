#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#define BASE_MAX 0xffffffffffffffff
#define N 4

void test_is_equal(int flag) {
    switch (flag) {
        case -1:
            printf("abs(a) is less than abs(b)\n");
            break;
        case 1:
            printf("abs(a) is greater than abs(b)\n");
            break;
        default:
            printf("abs(a) is equal to abs(b)\n");
    }
}

int main(int argc, char *argv[]) {
    // value comparison test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Value comparison test \n");
    
    printf("Comparison between two equal arguments \n");
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    int cmp_flag = lil_cmp_val(&a, &b);
    test_is_equal(cmp_flag);
    
    printf("Comparison between two unequal arguments \n");
    a.val[0] = 0x1234567;
    b.val[0] = 0x7654321;
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    cmp_flag = lil_cmp_val(&a, &b);
    test_is_equal(cmp_flag);
    
    printf("Comparison between two equal arguments of different size \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)calloc(b.size, sizeof(uint64_t));
    b.val = new_arr_b;
    a.val[0] = 0x1234567;
    b.val[0] = 0x1234567;
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    cmp_flag = lil_cmp_val(&a, &b);
    test_is_equal(cmp_flag);
    
    printf("Comparison between two unequal arguments of different size \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    for (int i = 0; i < a.size; a.val[i++] = BASE_MAX);
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    cmp_flag = lil_cmp_val(&a, &b);
    test_is_equal(cmp_flag);

    free(another_arr_b);
    return 0;
}
