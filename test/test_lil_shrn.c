#include <stdint.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_shrn, empty_value_right_n_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 48;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, most_significant_digit_right_0_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 0x000012345678abcd};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 0;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0, 0, 0, 0x000012345678abcd};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, most_significant_digit_right_16_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 0x000012345678abcd};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 16;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0, 0, 0x0000000012345678, 0xabcd000000000000};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, most_significant_digit_right_64_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 0x000012345678abcd};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 64;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0, 0, 0x000012345678abcd, 0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, most_significant_digit_right_96_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 0x000012345678abcd};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 96;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0, 0x5678abcd00000000, 0x0000000000001234, 0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, least_significant_digit_right_0_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0x000012345678abcd};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 0;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0x000012345678abcd};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, least_significant_digit_right_16_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0x000012345678abcd};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 16;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {0x0000000012345678};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, least_significant_digit_right_64_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {0x000012345678abcd};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 64;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, all_digits_are_set_right_16_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 16;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, 0x0000ffffffffffff};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, all_digits_are_set_right_48_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 64;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, 0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_shrn, all_digits_are_set_right_96_bits_shift) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = 96;
    int flag = lil_shrn(&a, n);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, 0x00000000ffffffff, 0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
