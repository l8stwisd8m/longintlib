#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "test_utils.h"
#include "../include/longintlib.h"

void test_len(lil_t *a) {
    uint64_t a_len = lil_len(a);
    PRINT_ARG(a);
    printf("len(a): %"PRIu64"\n", a_len);
}

int main(int argc, char *argv[]) {
    // length test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Length test \n");
    
    printf("Length of an empty value \n");
    test_len(&a);
    
    printf("Most significant digit is not null \n");
    a.val[N - 1] = 0x1234567;
    test_len(&a);
    
    printf("Least significant digit is not null \n");
    a.val[N - 1] = 0;
    a.val[0] = 0x1234567;
    test_len(&a);
    
    printf("All digits are \"full\" \n");
    for (int i = 0; i < N; a.val[i++] = BASE_MAX);
    test_len(&a);
    
    return 0;
}
