#include <stdint.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_cmp_len, two_empty_values_length_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_cmp_len(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp_len, two_equal_values_of_the_same_length_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x123456789};
    uint64_t arr_b[LIL_256_BIT] = {0x123456789};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_cmp_len(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp_len, two_unequal_values_of_the_same_length_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x123456789};
    uint64_t arr_b[LIL_256_BIT] = {0x123454321};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_cmp_len(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp_len, two_values_of_different_length_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x7654321};
    uint64_t arr_b[LIL_256_BIT] = {0x0123456789abcdef, 0xfedbca9876543210};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_cmp_len(&a, &b);
    cr_expect_eq(flag, -1);
    flag = lil_cmp_len(&b, &a);
    cr_expect_eq(flag, 1);
}
