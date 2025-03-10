#include <stdint.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_cmp_val, two_empty_values_value_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_cmp_val(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp_val, two_equal_values_of_the_same_size_value_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x123456789};
    uint64_t arr_b[LIL_256_BIT] = {0x123456789};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_cmp_val(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp_val, two_equal_values_of_different_size_value_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x123456789};
    uint64_t arr_b[LIL_256_BIT - 1] = {0x123456789};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT - 1};
    int flag = lil_cmp_val(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp_val, two_unequal_values_of_different_size_value_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x7654321};
    uint64_t arr_b[LIL_256_BIT - 1] = {0x0123456789abcdef, 0xfedbca9876543210};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT - 1};
    int flag = lil_cmp_val(&a, &b);
    cr_expect_eq(flag, -1);
    flag = lil_cmp_val(&b, &a);
    cr_expect_eq(flag, 1);
}
