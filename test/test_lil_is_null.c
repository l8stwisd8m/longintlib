#include <stdint.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_is_null, empty_value_is_null) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_is_null(&a);
    cr_expect_eq(flag, 1);
}

Test(test_lil_is_null, most_significant_digit_value_is_null) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_is_null(&a);
    cr_expect_eq(flag, 0);
}

Test(test_lil_is_null, least_significant_digit_value_is_null) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_is_null(&a);
    cr_expect_eq(flag, 0);
}

Test(test_lil_is_null, all_digits_are_set_value_is_null) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_is_null(&a);
    cr_expect_eq(flag, 0);
}
