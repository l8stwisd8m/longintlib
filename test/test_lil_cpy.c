#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void test_cpy(lil_t *a, lil_t *b) {
    PRINT_ARG(a);
    PRINT_ARG(b);
    lil_cpy(a, b);
    printf("a <- b:\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // copy test
    uint64_t arr_a[N] = {0};
    uint64_t *arr_b = (uint64_t *)malloc(N * sizeof(uint64_t));
    for (int i = 0; i < N; arr_b[i++] = BASE_MAX);
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Copy test \n");
    
    printf("Copy b to a (arguments have same size) \n");
    test_cpy(&a, &b);
    
    printf("Valid copy b to a (arguments have different sizes) \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)realloc(arr_b, b.size * sizeof(uint64_t));
    b.val = new_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    for (int i = 0; i < a.size; a.val[i++] = 0);
    test_cpy(&a, &b);
    
    printf("Invalid copy b to a (arguments have different sizes) \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    b.val = another_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    for (int i = 0; i < a.size; a.val[i++] = 0);
    test_cpy(&a, &b);
    
    free(another_arr_b);
    return 0;
}
