#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#define N 4

void test_is_null(int flag) {
    if (flag) printf("Value is null\n");
    else printf("Value is not null\n");
}

int main(int argc, char *argv[]) {
    // decrement test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Function \"is null\" test \n");
    
    printf("Empty value \n");
    int flag = lil_is_null(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_null(flag);
    
    printf("Most significant digit is not null \n");
    a.val[N - 1] = 1;
    flag = lil_is_null(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_null(flag);
     
    printf("Least significant digit is not null \n");
    a.val[N - 1] = 0;
    a.val[0] = 1;
    flag = lil_is_null(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_null(flag);
    
    return 0;
}
