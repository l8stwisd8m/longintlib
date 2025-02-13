#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "test_utils.h"
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void print_args(lil_t *a, lil_t *b) {
    printf("a:\t");
    lil_print_hex(a);
    printf("b:\t");
    lil_print_hex(b);
}

void sum(lil_t *a, lil_t *b, lil_t *c) {
    lil_sum(c, a, b);
    printf("a + b:\t");
    lil_print_hex(c);
    if (c->sign) printf("Result sign is minus \n");
    else printf("Result sign is plus \n");
}

void test_sum(lil_t *a, lil_t *b, lil_t *c) {
    PRINT_ARG(a);
    PRINT_ARG(b);
    
    printf("Both terms are positive \n");
    a->sign = LIL_PLUS; b->sign = LIL_PLUS;
    sum(a, b, c);
        
    printf("First term is positive, second one is negative \n");
    b->sign = LIL_MINUS;
    sum(a, b, c);
    
    printf("First term is negative, second one is positive \n");
    a->sign = LIL_MINUS; b->sign = LIL_PLUS;
    sum(a, b, c);
    
    printf("Both terms are negative \n");
    b->sign = LIL_MINUS;
    sum(a, b, c);
}

int main(int argc, char *argv[]) {
    // arithmetic sum test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    uint64_t arr_c[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    long_int c = {PLUS, arr_c, N};
    
    printf("Arithmetic sum test \n");
    
    printf("Sum of terms both equal to zero \n");
    print_args(&a, &b);
    sum(&a, &b, &c);
     
    printf("Sum of a term equal to zero and a non-zero value \n");
    a.val[0] = 0x01234567;
    test_sum(&a, &b, &c);
    
    printf("Sum of two equal terms of same size \n");
    a.val[1] = BASE_MAX; a.val[0] = 0xfedcba9876543210;
    b.val[1] = BASE_MAX; b.val[0] = 0xfedcba9876543210;
    test_sum(&a, &b, &c);
    
    printf("Sum of two equal terms of same size \n");
    a.val[0] = 0x0123456776543210;
    test_sum(&a, &b, &c);
    
    printf("Valid sum of different sized terms \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)malloc(b.size * sizeof(uint64_t));
    b.val = new_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_sum(&a, &b, &c);
    
    printf("Invalid sum of different sized terms \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    b.val = another_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_sum(&a, &b, &c);
    
    free(another_arr_b);
    return 0;
}
