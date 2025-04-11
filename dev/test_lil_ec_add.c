#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintcurve.h"

Test(test_lil_ec_add, special_point) {
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
    
    uint64_t arr_q_x[LIL_128_BIT] = {11};
    uint64_t arr_q_y[LIL_128_BIT] = {11};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
     
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_add(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_arr_eq(arr_r_x, arr_q_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, arr_q_y, LIL_128_BIT);
    
    arr_r_x[0] = 0; arr_r_y[0] = 0;
    lil_ec_add(&curve, &r, &q, &p);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_arr_eq(arr_r_x, arr_q_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, arr_q_y, LIL_128_BIT);
}

Test(test_lil_ec_add, sum_of_opposite_points) {
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
    uint64_t arr_q_y[LIL_128_BIT] = {40};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
     
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_add(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {0};
    uint64_t expected_y[LIL_128_BIT] = {0};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_add, case_denominator_is_null) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {2};
    uint64_t arr_p_y[LIL_128_BIT] = {15};
    long_int p_x = {PLUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {PLUS, arr_p_y, LIL_128_BIT};
    lil_point_t p = {&p_x, &p_y};
    
    uint64_t arr_q_x[LIL_128_BIT] = {18};
    uint64_t arr_q_y[LIL_128_BIT] = {28};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
     
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_add(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {3};
    uint64_t expected_y[LIL_128_BIT] = {3};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_add, case_denominator_is_not_null) {
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
    
    uint64_t arr_q_x[LIL_128_BIT] = {2};
    uint64_t arr_q_y[LIL_128_BIT] = {15};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
     
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_add(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {10};
    uint64_t expected_y[LIL_128_BIT] = {38};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_add, another_example) {
    uint64_t arr_a[LIL_128_BIT] = {0};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {97};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {1};
    uint64_t arr_p_y[LIL_128_BIT] = {0};
    long_int p_x = {PLUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {PLUS, arr_p_y, LIL_128_BIT};
    lil_point_t p = {&p_x, &p_y};
    
    uint64_t arr_q_x[LIL_128_BIT] = {1};
    uint64_t arr_q_y[LIL_128_BIT] = {0};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
     
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_add(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {0};
    uint64_t expected_y[LIL_128_BIT] = {0};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_add, another_example_2) {
    uint64_t arr_a[LIL_128_BIT] = {0};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {97};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {96};
    uint64_t arr_p_y[LIL_128_BIT] = {80};
    long_int p_x = {PLUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {PLUS, arr_p_y, LIL_128_BIT};
    lil_point_t p = {&p_x, &p_y};
    
    uint64_t arr_q_x[LIL_128_BIT] = {96};
    uint64_t arr_q_y[LIL_128_BIT] = {80};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
     
    uint64_t arr_r_x[LIL_128_BIT] = {0};
    uint64_t arr_r_y[LIL_128_BIT] = {0};
    long_int r_x = {PLUS, arr_r_x, LIL_128_BIT};
    long_int r_y = {PLUS, arr_r_y, LIL_128_BIT};
    lil_point_t r = {&r_x, &r_y};
    
    int flag = lil_ec_add(&curve, &r, &p, &q);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {13};
    uint64_t expected_y[LIL_128_BIT] = {81};
    cr_expect_arr_eq(arr_r_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_r_y, expected_y, LIL_128_BIT);
}
