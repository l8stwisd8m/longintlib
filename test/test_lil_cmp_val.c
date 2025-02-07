#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"

void verbose_cmp(int flag) {
    if (flag == -1) printf("value of a is less than b\n");
    if (flag == 1) printf("value of a is greater than value of b\n");
    if (flag == 0) printf("value of a is equal to value of b\n");
}

int main(int argc, char *argv[]) {
    // value comparison test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Value comparison test \n");
    
    printf("Comparison between two equal arguments \n");
    print_args(&a, &b);
    int cmp_flag = lil_cmp_val(&a, &b);
    verbose_cmp(cmp_flag);
    
    printf("Comparison between two unequal arguments \n");
    a.val[0] = 0x1234567;
    b.val[0] = 0x7654321;
    print_args(&a, &b);
    cmp_flag = lil_cmp_val(&a, &b);
    verbose_cmp(cmp_flag);
    
    printf("Comparison between two equal arguments of different size \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)calloc(b.size, sizeof(uint64_t));
    b.val = new_arr_b;
    a.val[0] = 0x1234567;
    b.val[0] = 0x1234567;
    print_args(&a, &b);
    cmp_flag = lil_cmp_val(&a, &b);
    verbose_cmp(cmp_flag);
    
    printf("Comparison between two unequal arguments of different size \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    for (int i = 0; i < a.size; a.val[i++] = BASE_MAX);
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    print_args(&a, &b);
    cmp_flag = lil_cmp_val(&a, &b);
    verbose_cmp(cmp_flag);

    free(another_arr_b);
    return 0;
}
