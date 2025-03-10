#include <limits.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_short_mul, short_multiplication_of_empty_values) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = 0;
    int flag = lil_short_mul(&a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_short_mul, most_significant_digit_short_multiplication) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    int flag = lil_short_mul(&a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_256_BIT] = {0, 0, 0, 0x00014b66dafaaf71};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_short_mul, least_significant_digit_short_multiplication) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = UINT64_MAX;
    int flag = lil_short_mul(&a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_256_BIT] = {0xfffffffffedcba99, 0x1234567 - 1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_short_mul, overflow_while_short_multiplication) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = UINT64_MAX;
    int flag = lil_short_mul(&a, b);
    cr_expect_eq(flag, LIL_OVERFLOW);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_256_BIT] = {1, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

