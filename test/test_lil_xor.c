#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#define BASE_MAX 0xffffffffffffffff
#define N 4

int main(int argc, char *argv[]) {
    // bitwise "xor" test
    uint64_t arr_a[N] = {BASE_MAX, 0, BASE_MAX, 0};
    uint64_t *arr_b = (uint64_t *)malloc(N * sizeof(uint64_t));
    arr_b[0] = 0; arr_b[1] = BASE_MAX;
    arr_b[2] = BASE_MAX; arr_b[3] = 0;
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Bitwise \"xor\" test \n");
    
    printf("Bitwise \"xor\" of same sized arguments \n");
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    lil_xor(&a, &b);
    printf("a ^ b:\t");
    lil_print_hex(&a);
     
    printf("Valid bitwise \"xor\" of different sized arguments \n");
    b.size = N - 1;
    uint64_t *new_arr_b = (uint64_t *)realloc(arr_b, b.size * sizeof(uint64_t));
    b.val = new_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    lil_xor(&a, &b);
    printf("a ^ b:\t");
    lil_print_hex(&a);
     
    printf("Invalid bitwise \"xor\" of different sized arguments \n");
    b.size = N + 1;
    uint64_t *another_arr_b = (uint64_t *)realloc(new_arr_b, b.size * sizeof(uint64_t));
    b.val = another_arr_b;
    for (int i = 0; i < b.size; b.val[i++] = BASE_MAX);
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    lil_xor(&a, &b);
    printf("a ^ b:\t");
    lil_print_hex(&a);
    
    free(another_arr_b);
    return 0;
}
