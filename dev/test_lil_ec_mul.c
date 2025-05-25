#include <criterion/criterion.h>
#include <stdint.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintcurve.h"

Test(test_lil_ec_mul, multiplication_of_special_point) {
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
    
    uint64_t arr_q_x[LIL_128_BIT] = {0};
    uint64_t arr_q_y[LIL_128_BIT] = {0};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
    
    uint64_t arr_n[LIL_128_BIT] = {10};
    long_int n = {PLUS, arr_n, LIL_128_BIT};
    
    int flag = lil_ec_mul(&curve, &p, &q, &n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {0};
    uint64_t expected_y[LIL_128_BIT] = {0};
    cr_expect_arr_eq(arr_p_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_p_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_mul, multiplication_by_zero) {
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
    
    uint64_t arr_n[LIL_128_BIT] = {0};
    long_int n = {PLUS, arr_n, LIL_128_BIT};
    
    int flag = lil_ec_mul(&curve, &p, &q, &n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {0};
    uint64_t expected_y[LIL_128_BIT] = {0};
    cr_expect_arr_eq(arr_p_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_p_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_mul, multiplication_by_one) {
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
    
    uint64_t arr_n[LIL_128_BIT] = {1};
    long_int n = {PLUS, arr_n, LIL_128_BIT};
    
    int flag = lil_ec_mul(&curve, &p, &q, &n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {11};
    uint64_t expected_y[LIL_128_BIT] = {11};
    cr_expect_arr_eq(arr_p_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_p_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_mul, multiplication_example_1) {
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
    
    uint64_t arr_n[LIL_128_BIT] = {1000};
    long_int n = {PLUS, arr_n, LIL_128_BIT};
    
    int flag = lil_ec_mul(&curve, &p, &q, &n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {11};
    uint64_t expected_y[LIL_128_BIT] = {32};
    cr_expect_arr_eq(arr_p_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_p_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_mul, multiplication_example_2) {
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
    
    uint64_t arr_n[LIL_128_BIT] = {10};
    long_int n = {PLUS, arr_n, LIL_128_BIT};
    
    int flag = lil_ec_mul(&curve, &p, &q, &n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {3};
    uint64_t expected_y[LIL_128_BIT] = {40};
    cr_expect_arr_eq(arr_p_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_p_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_mul, multiplication_example_3) {
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
    
    uint64_t arr_n[LIL_128_BIT] = {11};
    long_int n = {PLUS, arr_n, LIL_128_BIT};
    
    int flag = lil_ec_mul(&curve, &p, &q, &n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {0};
    uint64_t expected_y[LIL_128_BIT] = {0};
    cr_expect_arr_eq(arr_p_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_p_y, expected_y, LIL_128_BIT);
}

Test(test_lil_ec_mul, multiplication_example_4) {
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
    
    uint64_t arr_q_x[LIL_128_BIT] = {39};
    uint64_t arr_q_y[LIL_128_BIT] = {31};
    long_int q_x = {PLUS, arr_q_x, LIL_128_BIT};
    long_int q_y = {PLUS, arr_q_y, LIL_128_BIT};
    lil_point_t q = {&q_x, &q_y};
    
    uint64_t arr_n[LIL_128_BIT] = {11};
    long_int n = {PLUS, arr_n, LIL_128_BIT};
    
    int flag = lil_ec_mul(&curve, &p, &q, &n);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_x[LIL_128_BIT] = {39};
    uint64_t expected_y[LIL_128_BIT] = {31};
    cr_expect_arr_eq(arr_p_x, expected_x, LIL_128_BIT);
    cr_expect_arr_eq(arr_p_y, expected_y, LIL_128_BIT);
}
