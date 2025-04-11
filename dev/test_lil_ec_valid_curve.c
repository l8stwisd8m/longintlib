#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintcurve.h"

Test(test_lil_ec_valid_curve, valid_curve) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    int flag = lil_ec_valid_curve(&curve);
    cr_expect_eq(flag, 1);
}

Test(test_lil_ec_valid_curve, invalid_curve) {
    uint64_t arr_a[LIL_128_BIT] = {2};
    uint64_t arr_b[LIL_128_BIT] = {3};
    uint64_t arr_m[LIL_128_BIT] = {5};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {PLUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    int flag = lil_ec_valid_curve(&curve);
    cr_expect_eq(flag, 0);
}
