#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"

void test_print_dec(lil_t *a) {
    printf("a:\t");
    lil_print_dec(a);
}

int main(int argc, char *argv[]) {
    // decimal print test
    uint64_t arr_a[1] = {0x1234567};
    long_int a = {PLUS, arr_a, 1};
    
    printf("Decimal print test \n");
    
    printf("Single digit value \n");
    test_print_dec(&a);
    
    printf("Odd amount of digits \n");
    a.size = 3;
    uint64_t *new_arr_a = (uint64_t *)malloc(a.size * sizeof(uint64_t));
    for (int i = 0; i < a.size; i++) new_arr_a[i] = 1 + i;
    a.val = new_arr_a;
    test_print_dec(&a);
    
    printf("Even amount of digits \n");
    a.size = 4;
    uint64_t *another_arr_a = (uint64_t *)realloc(new_arr_a, a.size * sizeof(uint64_t));
    for (int i = 0; i < a.size; i++) another_arr_a[i] = 1 + i;
    a.val = another_arr_a;
    test_print_dec(&a);
    
    free(another_arr_a);
    return 0;
}
