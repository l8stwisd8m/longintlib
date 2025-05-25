#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_mul, multiplication_of_empty_values) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0};
    uint64_t arr_c[LIL_512_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_512_BIT};
    int flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_512_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

void fork_test_lil_mul(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_b[LIL_256_BIT] = {1};
        uint64_t arr_c[LIL_256_BIT + 2] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT};
        long_int c = {PLUS, arr_c, LIL_256_BIT + 2};
        lil_mul(&c, &a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_mul, invalid_sized_terms_multiplication) {
    int status;
    fork_test_lil_mul();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_mul, multiplication_of_empty_and_not_empty_values) {
    uint64_t arr_a[LIL_256_BIT] = {1, 2, 3, 4};
    uint64_t arr_b[LIL_256_BIT] = {0};
    uint64_t arr_c[LIL_512_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_512_BIT};
    // both terms are positive
    int flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_512_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // second term is positive, first one is negative
    b.sign = LIL_PLUS; a.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // both terms are negative 
    b.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_mul, multiplication_of_two_equal_terms) {
    uint64_t arr_a[LIL_128_BIT] = {0xfedcba9876543210, UINT64_MAX};
    uint64_t arr_b[LIL_128_BIT] = {0xfedcba9876543210, UINT64_MAX};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    long_int b = {PLUS, arr_b, LIL_128_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    // both terms are positive
    int flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0xdeec6cd7a44a4100, 0x00014b66dc33f6ac, 0xfdb97530eca86420, UINT64_MAX};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // second term is positive, first one is negative
    b.sign = LIL_PLUS; a.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // both terms are negative 
    b.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_mul, multiplication_of_two_unequal_terms) {
    uint64_t arr_a[LIL_128_BIT] = {0xfedcba9876543210, UINT64_MAX};
    uint64_t arr_b[LIL_128_BIT] = {0x0123456776543210, UINT64_MAX};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    long_int b = {PLUS, arr_b, LIL_128_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    // both terms are positive
    int flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0xc05d87c7a44a4100, 0x0121fa00ad8dd917, 0xffffffffeca86420, UINT64_MAX - 1};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // second term is positive, first one is negative
    b.sign = LIL_PLUS; a.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // both terms are negative 
    b.sign = LIL_MINUS;
    flag = lil_mul(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}
