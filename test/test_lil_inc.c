#include <stdio.h>
#include <stdint.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"

void test_inc(lil_t *a) {
    printf("a:\t");
    lil_print_hex(a);
    lil_dec(a);
    printf("dec(a):\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // increment test
    uint64_t arr_a[N] = {BASE_MAX, BASE_MAX, BASE_MAX, 0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Increment test \n");
    
    printf("Most significant digit increment \n");
    test_inc(&a);
    
    printf("Least significant digit increment \n");
    for (int i = 0; i < N; a.val[i++] = 0);
    test_inc(&a);
    
    printf("An overflaw caused by increment of a \"full\" value \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    test_inc(&a);
    
    return 0;
}
