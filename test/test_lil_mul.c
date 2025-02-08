#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#define M 8

void mul(lil_t *a, lil_t *b, lil_t *c) {
    lil_mul(c, a, b);
    printf("a * b:\t");
    lil_print_hex(c);
    if (c->sign) printf("Result sign is minus \n");
    else printf("Result sign is plus \n");
}

void test_mul(lil_t *a, lil_t *b, lil_t *c) {
    print_args(a, b);
    
    printf("Both terms are positive \n");
    a->sign = LIL_PLUS; b->sign = LIL_PLUS;
    mul(a, b, c);
        
    printf("First term is positive, second one is negative \n");
    b->sign = LIL_MINUS;
    mul(a, b, c);
    
    printf("First term is negative, second one is positive \n");
    a->sign = LIL_MINUS; b->sign = LIL_PLUS;
    mul(a, b, c);
    
    printf("Both terms are negative \n");
    b->sign = LIL_MINUS;
    mul(a, b, c);
}

int main(int argc, char *argv[]) {
    // multiplication test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    uint64_t arr_c[M] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    long_int c = {PLUS, arr_c, M};
    
    printf("Multiplication test \n");
    
    printf("Multiplication of terms both equal to zero \n");
    print_args(&a, &b);
    mul(&a, &b, &c);
     
    printf("Multiplication of a term equal to zero and a non-zero value \n");
    a.val[0] = 0x01234567;
    test_mul(&a, &b, &c);
    
    printf("Multiplication of two equal terms of same size \n");
    a.val[1] = BASE_MAX; a.val[0] = 0xfedcba9876543210;
    b.val[1] = BASE_MAX; b.val[0] = 0xfedcba9876543210;
    test_mul(&a, &b, &c);
    
    printf("Multiplication of two equal terms of same size \n");
    a.val[0] = 0x0123456776543210;
    test_mul(&a, &b, &c);
    
    printf("Valid multiplication of different sized terms \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)malloc(b.size * sizeof(uint64_t));
    b.val = new_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_mul(&a, &b, &c);
    
    printf("Invalid multiplication of different sized terms \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    b.val = another_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_mul(&a, &b, &c);
    
    free(another_arr_b);
    return 0;
}
