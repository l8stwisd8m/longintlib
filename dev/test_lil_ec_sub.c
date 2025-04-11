#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintcurve.h"

Test(test_lil_ec_sub, result_is_special_point) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {3};
    uint64_t arr_p_y[LIL_128_BIT] = {3};
    long_int p_x = {PLUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {PLUS, arr_p_y, LIL_128_BIT};
    lil_point_t p = {&p_x, &p_y};
    
    uint64_t arr_q_x[LIL_128_BIT] = {3};
    uint64_t arr_q_y[LIL_128_BIT] = {3};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
    
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_sub(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {0};
    uint64_t expected_y[LIL_128_BIT] = {0};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_sub, result_is_not_special_point) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {11};
    uint64_t arr_p_y[LIL_128_BIT] = {11};
    long_int p_x = {PLUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {PLUS, arr_p_y, LIL_128_BIT};
    lil_point_t p = {&p_x, &p_y};
    
    uint64_t arr_q_x[LIL_128_BIT] = {13};
    uint64_t arr_q_y[LIL_128_BIT] = {1};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
    
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_sub(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {12};
    uint64_t expected_y[LIL_128_BIT] = {38};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_sub, point_p_is_special) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {0};
    uint64_t arr_p_y[LIL_128_BIT] = {0};
    long_int p_x = {PLUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {PLUS, arr_p_y, LIL_128_BIT};
    lil_point_t p = {&p_x, &p_y};
    
    uint64_t arr_q_x[LIL_128_BIT] = {3};
    uint64_t arr_q_y[LIL_128_BIT] = {3};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
    
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_sub(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {3};
    uint64_t expected_y[LIL_128_BIT] = {40};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_sub, point_q_is_special) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {3};
    uint64_t arr_p_y[LIL_128_BIT] = {3};
    long_int p_x = {PLUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {PLUS, arr_p_y, LIL_128_BIT};
    lil_point_t p = {&p_x, &p_y};
    
    uint64_t arr_q_x[LIL_128_BIT] = {0};
    uint64_t arr_q_y[LIL_128_BIT] = {0};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
    
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_sub(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {3};
    uint64_t expected_y[LIL_128_BIT] = {3};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}
