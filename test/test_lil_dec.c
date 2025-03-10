#include <stdint.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_dec, most_significant_digit_decrement) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_dec(&a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, 0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_dec, least_significant_digit_decrement) {
    uint64_t arr_a[LIL_256_BIT] = {2, 0, 0, 0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_dec(&a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {1, 0, 0, 0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_dec, overflow_while_decrement) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_dec(&a);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
