#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void test_sub(lil_t *a, lil_t *b) {
    PRINT_ARG(a);
    PRINT_ARG(b);
    lil_sub(a, b);
    printf("a - b:\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // subtraction test
    uint64_t arr_a[N] = {0, BASE_MAX, BASE_MAX, 0};
    uint64_t arr_b[N] = {BASE_MAX, 0, BASE_MAX, 0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Subtraction test \n");
    
    printf("Subtraction of same sized arguments \n");
    test_sub(&a, &b);
     
    printf("An overflow caused by subtraction \n");
    for (int i = 0; i < N; i++) {
        a.val[i] = 0;
        b.val[i] = 0;
    }
    b.val[0] = 1;
    test_sub(&a, &b);

    printf("Valid subtraction of different sized arguments \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)malloc(b.size * sizeof(uint64_t));
    b.val = new_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_sub(&a, &b);
    
    printf("Invalid subtraction of different sized arguments \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    b.val = another_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_sub(&a, &b);
    
    free(another_arr_b);
    return 0;
}
