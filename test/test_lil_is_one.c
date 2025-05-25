#include <stdint.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_is_one, empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_is_one(&a);
    cr_expect_eq(flag, 0);
}

Test(test_lil_is_one, most_significant_digit_value_is_one) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_is_one(&a);
    cr_expect_eq(flag, 0);
}

Test(test_lil_is_one, least_significant_digit_value_is_one) {
    uint64_t arr_a[LIL_256_BIT] = {1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_is_one(&a);
    cr_expect_eq(flag, 1);
}

Test(test_lil_is_one, all_digits_are_set) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_is_one(&a);
    cr_expect_eq(flag, 0);
}
