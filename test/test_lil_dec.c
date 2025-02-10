#include <stdio.h>
#include <stdint.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void test_dec(lil_t *a) {
    printf("a:\t");
    lil_print_hex(a);
    lil_dec(a);
    printf("dec(a):\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // decrement test
    uint64_t arr_a[N] = {BASE_MAX};
    long_int a = {PLUS, arr_a, N};
    
    printf("Decrement test \n");
    
    printf("Least significant digit decrement \n");
    test_dec(&a);
    
    printf("Most significant digit decrement \n");
    a.val[0] = 0;
    a.val[N - 1] = BASE_MAX;
    test_dec(&a);
    
    printf("An overflaw caused by decrement of an empty value\n");
    for (int i = 0; i < N; a.val[i++] = 0);
    test_dec(&a);
    
    return 0;
}
