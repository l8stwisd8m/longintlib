#include <stdint.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_shl, empty_value_left_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_shl(&a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shl, most_significant_digit_left_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_shl(&a);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {0, 0, 0, UINT64_MAX << 1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shl, least_significant_digit_left_shift) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_shl(&a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {UINT64_MAX - 1, 1, 0, 0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shl, middle_digits_left_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0, UINT64_MAX, UINT64_MAX, 0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_shl(&a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0, UINT64_MAX - 1, UINT64_MAX, 1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
