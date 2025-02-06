#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#define N 4

void test_is_odd(int flag) {
    if (flag) printf("Value is odd\n");
    else printf("Value is not odd\n");
}

int main(int argc, char *argv[]) {
    // is odd test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Function \"is odd\" test \n");
    
    printf("Empty value \n");
    int flag = lil_is_odd(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_odd(flag);
    
    printf("Least significant digit is odd \n");
    a.val[0] = 1;
    flag = lil_is_odd(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_odd(flag);
     
    printf("Most significant digit is even \n");
    a.val[0] = 2;
    flag = lil_is_odd(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_odd(flag);
    
    return 0;
}
