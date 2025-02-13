#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "test_utils.h"

void test_rev(lil_t *a) {
    PRINT_ARG(a);
    lil_rev(a);
    printf("rev(a):\t");
    lil_print_hex(a);
}

int main(int argc, char *argv[]) {
    // reverse test
    uint64_t arr_a[1] = {1};
    long_int a = {PLUS, arr_a, 1};
    
    printf("Value reverse test \n");
    
    printf("Single digit value \n");
    test_rev(&a);
    
    printf("Odd amount of digits \n");
    a.size = 3;
    uint64_t *new_arr_a = (uint64_t *)malloc(a.size * sizeof(uint64_t));
    for (int i = 0; i < a.size; i++) new_arr_a[i] = 1 + i;
    a.val = new_arr_a;
    test_rev(&a);
    
    printf("Even amount of digits \n");
    a.size = 4;
    uint64_t *another_arr_a = (uint64_t *)realloc(new_arr_a, a.size * sizeof(uint64_t));
    for (int i = 0; i < a.size; i++) another_arr_a[i] = 1 + i;
    a.val = another_arr_a;
    test_rev(&a);
    
    free(another_arr_a);
    return 0;
}
