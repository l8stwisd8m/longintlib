#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintcurve.h"

Test(test_lil_ec_valid_point, special_point) {
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
    long_int p_y = {MINUS, arr_p_y, LIL_128_BIT};
    lil_point_t point = {&p_x, &p_y};
    
    int flag = lil_ec_valid_point(&curve, &point);
    cr_expect_eq(flag, LIL_EC_SPECIAL);
}

Test(test_lil_ec_valid_point, positive_coordinates_invalid_point) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {1};
    uint64_t arr_p_y[LIL_128_BIT] = {1};
    long_int p_x = {PLUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {PLUS, arr_p_y, LIL_128_BIT};
    lil_point_t point = {&p_x, &p_y};
    
    int flag = lil_ec_valid_point(&curve, &point);
    cr_expect_eq(flag, 0);
}

Test(test_lil_ec_valid_point, positive_coordinates_valid_point) {
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
    lil_point_t point = {&p_x, &p_y};
    
    int flag = lil_ec_valid_point(&curve, &point);
    cr_expect_eq(flag, 1);
}

Test(test_lil_ec_valid_point, negative_coordinates_invalid_point) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {1};
    uint64_t arr_p_y[LIL_128_BIT] = {1};
    long_int p_x = {MINUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {MINUS, arr_p_y, LIL_128_BIT};
    lil_point_t point = {&p_x, &p_y};
    
    int flag = lil_ec_valid_point(&curve, &point);
    cr_expect_eq(flag, 0);
}

Test(test_lil_ec_valid_point, negative_coordinates_valid_point) {
    uint64_t arr_a[LIL_128_BIT] = {23};
    uint64_t arr_b[LIL_128_BIT] = {1};
    uint64_t arr_m[LIL_128_BIT] = {43};
    long_int a = {PLUS, arr_a, LIL_128_BIT}; 
    long_int b = {MINUS, arr_b, LIL_128_BIT};
    long_int m = {PLUS, arr_m, LIL_128_BIT};
    lil_ec_t curve = {&a, &b, &m};
    
    uint64_t arr_p_x[LIL_128_BIT] = {11};
    uint64_t arr_p_y[LIL_128_BIT] = {36};
    long_int p_x = {MINUS, arr_p_x, LIL_128_BIT};
    long_int p_y = {MINUS, arr_p_y, LIL_128_BIT};
    lil_point_t point = {&p_x, &p_y};
    
    int flag = lil_ec_valid_point(&curve, &point);
    cr_expect_eq(flag, 1);
}
