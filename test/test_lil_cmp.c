#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void verbose_cmp(int flag) {
    if (flag == -1) printf("a is less than b\n");
    if (flag == 1) printf("a is greater than b\n");
    if (flag == 0) printf("a is equal to b\n");
}

void comparison(lil_t *a, lil_t *b, int flag) {
    PRINT_ARG(a);
    PRINT_ARG(b);
    
    printf("Both values are positive \n");
    a->sign = PLUS; b->sign = PLUS;
    flag = lil_cmp(a, b);
    verbose_cmp(flag);
    
    printf("First value is negative, second one is positive \n");
    a->sign = MINUS;
    flag = lil_cmp(a, b);
    verbose_cmp(flag);
    
    printf("Both values are negative \n");
    b->sign = MINUS;
    flag = lil_cmp(a, b);
    verbose_cmp(flag);
}

int main(int argc, char *argv[]) {
    // comparison test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Comparison test \n");
    
    printf("Comparison between two equal arguments \n");
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    int cmp_flag = lil_cmp(&a, &b);
    verbose_cmp(cmp_flag);
    
    printf("Comparison between two equal arguments \n");
    a.val[0] = 0x1234567;
    b.val[0] = 0x1234567;
    comparison(&a, &b, cmp_flag);
    
    printf("Comparison between two unequal arguments \n");
    b.val[0] = 0x7654321;
    comparison(&a, &b, cmp_flag);
    
    printf("Comparison between two equal arguments of different size \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)calloc(b.size, sizeof(uint64_t));
    b.val = new_arr_b;
    b.val[0] = 0x1234567;
    comparison(&a, &b, cmp_flag);
    
    printf("Comparison between two unequal arguments of different size \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    b.val = another_arr_b;
    for (int i = 0; i < a.size; a.val[i++] = BASE_MAX);
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    comparison(&a, &b, cmp_flag);
    
    free(another_arr_b);
    return 0;
}
