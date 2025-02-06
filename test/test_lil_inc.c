#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#define BASE_MAX 0xffffffffffffffff
#define N 4

int main(int argc, char *argv[]) {
    // increment test
    uint64_t arr_a[N] = {BASE_MAX, BASE_MAX, BASE_MAX, 0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Increment test \n");
    
    printf("Most significant digit increment \n");
    printf("a:\t");
    lil_print_hex(&a);
    lil_inc(&a);
    printf("inc(a):\t");
    lil_print_hex(&a);
     
    printf("Least significant digit increment \n");
    for (int i = 0; i < N; a.val[i++] = 0);
    printf("a:\t");
    lil_print_hex(&a);
    lil_inc(&a);
    printf("inc(a):\t");
    lil_print_hex(&a);
     
    printf("An overflaw caused by increment of a \"full\" value \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    printf("a:\t");
    lil_print_hex(&a);
    lil_inc(&a);
    printf("inc(a):\t");
    lil_print_hex(&a);
    
    return 0;
}
