#include <stdint.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_rev, single_digit_value_reversed_digits_order) {
    uint64_t arr_a[1] = {1};
    long_int a = {PLUS, arr_a, 1};
    lil_rev(&a);
    uint64_t expected_arr[1] = {1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_rev, odd_amount_of_digits_value_reversed_digits_order) {
    uint64_t arr_a[LIL_256_BIT - 1] = {1, 2, 3};
    long_int a = {PLUS, arr_a, LIL_256_BIT - 1};
    lil_rev(&a);
    uint64_t expected_arr[LIL_256_BIT - 1] = {3, 2, 1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_rev, even_amount_of_digits_value_reversed_digits_order) {
    uint64_t arr_a[LIL_256_BIT] = {1, 2, 3, 4};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    lil_rev(&a);
    uint64_t expected_arr[LIL_256_BIT] = {4, 3, 2, 1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
