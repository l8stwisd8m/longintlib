#include <stdio.h>
#include <stdint.h>
#include "utils/test_utils.h"
#include "../include/longintlib.h"

void verbose_cmp_len(int flag) {
    if (flag == -1) printf("len(a) is less than len(b)\n");
    if (flag == 1) printf("len(a) is greater than len(b)\n");
    if (flag == 0) printf("len(a) is equal to len(b)\n");
}

int main(int argc, char *argv[]) {
    // length comparison test
    uint64_t arr_a[N] = {0};
    uint64_t arr_b[N] = {0};
    long_int a = {PLUS, arr_a, N};
    long_int b = {PLUS, arr_b, N};
    
    printf("Lenth comparison test \n");
    
    printf("Comparison between two equal arguments \n");
    print_args(&a, &b);
    int cmp_flag = lil_cmp_len(&a, &b);
    verbose_cmp_len(cmp_flag);
    
    printf("Comparison between arguments of the same length \n");
    a.val[0] = 0x1234567;
    b.val[0] = 0x1234321;
    print_args(&a, &b);
    cmp_flag = lil_cmp_len(&a, &b);
    verbose_cmp_len(cmp_flag);
    
    printf("Comparison between two unequal arguments \n");
    for (int i = 0; i < N; a.val[i] = 0, b.val[i] = BASE_MAX, i++);
    print_args(&a, &b);
    cmp_flag = lil_cmp_len(&a, &b);
    verbose_cmp_len(cmp_flag);
    cmp_flag = lil_cmp_len(&b, &a);
    verbose_cmp_len(cmp_flag);

    return 0;
}
