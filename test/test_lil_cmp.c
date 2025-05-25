#include <stdint.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_cmp, two_empty_values_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT - 1] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT - 1};
    int flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp, two_equal_values_of_the_same_size_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 0);
    b.sign = LIL_MINUS;
    flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 1);
    a.sign = LIL_MINUS;
    flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp, two_unequal_values_of_the_same_size_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT] = {0x7654321};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, -1);
    b.sign = LIL_MINUS;
    flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 1);
    a.sign = LIL_MINUS;
    flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 1);
}

Test(test_lil_cmp, two_equal_values_of_different_size_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT - 1] = {0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT - 1};
    int flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 0);
    b.sign = LIL_MINUS;
    flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 1);
    a.sign = LIL_MINUS;
    flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 0);
}

Test(test_lil_cmp, two_unequal_values_of_different_size_comparison) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT - 1] = {0x7654321};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT - 1};
    int flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, -1);
    b.sign = LIL_MINUS;
    flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 1);
    a.sign = LIL_MINUS;
    flag = lil_cmp(&a, &b);
    cr_expect_eq(flag, 1);
}
