#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintcurve.h"

Test(test_lil_ec_evaluate, evaluation_of_value_equal_to_zero) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p[LIL_128_BIT] = {0};
    uint64_t arr_q[LIL_128_BIT] = {0};
    long_int p = {MINUS, arr_p, LIL_128_BIT};
    long_int q = {MINUS, arr_q, LIL_128_BIT};   
    
    int flag = lil_ec_evaluate(&curve, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(p.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {42};
    cr_expect_arr_eq(p.val, expected_arr, p.size);
}

Test(test_lil_ec_evaluate, evaluation_of_value_equal_to_one) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p[LIL_128_BIT] = {0};
    uint64_t arr_q[LIL_128_BIT] = {1};
    long_int p = {PLUS, arr_p, LIL_128_BIT};
    long_int q = {PLUS, arr_q, LIL_128_BIT};   
    
    int flag = lil_ec_evaluate(&curve, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(p.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {23};
    cr_expect_arr_eq(p.val, expected_arr, p.size);
}

Test(test_lil_ec_evaluate, evaluation_of_positive_value) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p[LIL_128_BIT] = {0};
    uint64_t arr_q[LIL_128_BIT] = {10};
    long_int p = {PLUS, arr_p, LIL_128_BIT};
    long_int q = {PLUS, arr_q, LIL_128_BIT};   
    
    int flag = lil_ec_evaluate(&curve, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(p.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {25};
    cr_expect_arr_eq(p.val, expected_arr, p.size);
}

Test(test_lil_ec_evaluate, evaluation_of_negative_value) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p[LIL_128_BIT] = {0};
    uint64_t arr_q[LIL_128_BIT] = {10};
    long_int p = {MINUS, arr_p, LIL_128_BIT};
    long_int q = {MINUS, arr_q, LIL_128_BIT};   
    
    int flag = lil_ec_evaluate(&curve, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(p.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {16};
    cr_expect_arr_eq(p.val, expected_arr, p.size);
}
