#include <stdint.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_len, empty_value_bit_length) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = lil_len(&a);
    cr_expect_eq(n, 0);
}

Test(test_lil_len, most_significant_digit_bit_length) {
    uint64_t arr_a[LIL_256_BIT] = {0, 0, 0, 0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = lil_len(&a);
    cr_expect_eq(n, 217);
}

Test(test_lil_len, least_significant_digit_bit_length) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = lil_len(&a);
    cr_expect_eq(n, 25);
}

Test(test_lil_len, all_digits_are_set_bit_length) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    uint64_t n = lil_len(&a);
    cr_expect_eq(n, 256);
}
