#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_short_add, most_significant_digit_addition) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    int flag = lil_short_add(&a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0x1234567, 0, 0, UINT64_MAX};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_short_add, least_significant_digit_addition) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    int flag = lil_short_add(&a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0x1234567 - 1, 1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_short_add, overflow_while_addition) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t b = 1;
    int flag = lil_short_add(&a, b);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
