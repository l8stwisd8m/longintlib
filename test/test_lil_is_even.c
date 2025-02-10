#include <stdio.h>
#include <stdint.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void test_is_even(lil_t *a) {
    PRINT_ARG(a);
    int flag = lil_is_even(a);
    if (flag) printf("Value is even\n");
    else printf("Value is not even\n");
}

int main(int argc, char *argv[]) {
    // is even test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Function \"is even\" test \n");
    
    printf("Empty value \n");
    test_is_even(&a);
    
    printf("Least significant digit is odd \n");
    a.val[0] = 1;
    test_is_even(&a);
    
    printf("Most significant digit is even \n");
    a.val[0] = 2;
    test_is_even(&a);
    
    return 0;
}
