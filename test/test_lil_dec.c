#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#define BASE_MAX 0xffffffffffffffff
#define N 4

int main(int argc, char *argv[]) {
    // decrement test
    uint64_t arr_a[N] = {BASE_MAX};
    long_int a = {PLUS, arr_a, N};
    
    printf("Decrement test \n");
    
    printf("Least significant digit decrement \n");
    printf("a:\t");
    lil_print_hex(&a);
    lil_dec(&a);
    printf("dec(a):\t");
    lil_print_hex(&a);
     
    printf("Most significant digit decrement \n");
    a.val[0] = 0;
    a.val[N - 1] = BASE_MAX;
    printf("a:\t");
    lil_print_hex(&a);
    lil_dec(&a);
    printf("dec(a):\t");
    lil_print_hex(&a);
     
    printf("An overflaw caused by decrement of an empty value\n");
    for (int i = 0; i < N; a.val[i++] = 0);
    printf("a:\t");
    lil_print_hex(&a);
    lil_dec(&a);
    printf("dec(a):\t");
    lil_print_hex(&a);
    
    return 0;
}
