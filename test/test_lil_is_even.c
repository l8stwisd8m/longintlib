#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#define N 4

void test_is_even(int flag) {
    if (flag) printf("Value is even\n");
    else printf("Value is not even\n");
}

int main(int argc, char *argv[]) {
    // is even test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Function \"is even\" test \n");
    
    printf("Empty value \n");
    int flag = lil_is_even(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_even(flag);
    
    printf("Least significant digit is odd \n");
    a.val[0] = 1;
    flag = lil_is_even(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_even(flag);
     
    printf("Most significant digit is even \n");
    a.val[0] = 2;
    flag = lil_is_even(&a);
    printf("a:\t");
    lil_print_hex(&a);
    test_is_even(flag);
    
    return 0;
}
