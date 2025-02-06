#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#define BASE_MAX 0xffffffffffffffff
#define N 4

void test_is_equal(int flag) {
    switch (flag) {
        case -1:
            printf("len(a) is less than len(b)\n");
            break;
        case 1:
            printf("len(a) is greater than len(b)\n");
            break;
        default:
            printf("len(a) is equal to len(b)\n");
    }
}

int main(int argc, char *argv[]) {
    // length comparison test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Lenth comparison test \n");
    
    printf("Comparison between two equal arguments \n");
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    int cmp_flag = lil_cmp_len(&a, &b);
    test_is_equal(cmp_flag);
    
    printf("Comparison between arguments of the same length \n");
    a.val[0] = 0x1234567;
    b.val[0] = 0x1234321;
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    cmp_flag = lil_cmp_len(&a, &b);
    test_is_equal(cmp_flag);
    
    printf("Comparison between two unequal arguments \n");
    for (int i = 0; i < N; a.val[i] = 0, b.val[i] = BASE_MAX, i++);
    printf("a:\t");
    lil_print_hex(&a);
    printf("b:\t");
    lil_print_hex(&b);
    cmp_flag = lil_cmp_len(&a, &b);
    test_is_equal(cmp_flag);
    cmp_flag = lil_cmp_len(&b, &a);
    test_is_equal(cmp_flag);

    return 0;
}
