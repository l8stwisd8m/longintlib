#include <stdio.h>
#include <stdint.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void test_is_odd(lil_t *a) {
    PRINT_ARG(a);
    int flag = lil_is_odd(a);
    if (flag) printf("Value is odd\n");
    else printf("Value is not odd\n");
}

int main(int argc, char *argv[]) {
    // is odd test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Function \"is odd\" test \n");
    
    printf("Empty value \n");
    test_is_odd(&a);
    
    printf("Least significant digit is odd \n");
    a.val[0] = 1;
    test_is_odd(&a);
    
    printf("Most significant digit is even \n");
    a.val[0] = 2;
    test_is_odd(&a);
    
    return 0;
}
