#include <stdio.h>
#include <stdint.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"

void test_is_null(lil_t *a) {
    printf("a:\t");
    lil_print_hex(a);
    int flag = lil_is_null(a);
    if (flag) printf("Value is null\n");
    else printf("Value is not null\n");
}

int main(int argc, char *argv[]) {
    // decrement test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Function \"is null\" test \n");
    
    printf("Empty value \n");
    test_is_null(&a);
    
    printf("Most significant digit is not null \n");
    a.val[N - 1] = 1;
    test_is_null(&a);
    
    printf("Least significant digit is not null \n");
    a.val[N - 1] = 0;
    a.val[0] = 1;
    test_is_null(&a);
    
    return 0;
}
