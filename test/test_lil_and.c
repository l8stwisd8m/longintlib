#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void test_and(lil_t *a, lil_t *b) {
    PRINT_ARG(a);
    PRINT_ARG(b);
    lil_and(a, b);
    printf("a & b:\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // bitwise "and" test
    uint64_t arr_a[N] = {BASE_MAX, 0, BASE_MAX, 0};
    uint64_t arr_b[N] = {0, BASE_MAX, BASE_MAX, 0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Bitwise \"and\" test \n");
    
    printf("Bitwise \"and\" of same sized arguments \n");
    test_and(&a, &b);
    
    printf("Valid bitwise \"and\" of different sized arguments \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)malloc(b.size * sizeof(uint64_t));
    b.val = new_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_and(&a, &b);
    
    printf("Invalid bitwise \"and\" of different sized arguments \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    b.val = another_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    test_and(&a, &b);
    
    free(another_arr_b);
    return 0;
}
