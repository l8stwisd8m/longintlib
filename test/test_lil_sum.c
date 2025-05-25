#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_sum, sum_of_empty_values) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_sum, overflow_while_sum) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {1};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_OVERFLOW);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_sum, sum_of_not_empty_and_empty_values) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT] = {0};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    // both terms are positive
    int flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x1234567};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_sum(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // second term is positive, first one is negative
    flag = lil_sum(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // both terms are negative
    a.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_sum(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

void fork_test_lil_sum(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_b[LIL_256_BIT + 1] = {1};
        uint64_t arr_c[LIL_256_BIT - 1] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT + 1};
        long_int c = {PLUS, arr_c, LIL_256_BIT - 1};
        lil_sum(&c, &a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_sum, invalid_sized_terms_sum) {
    int status;
    fork_test_lil_sum();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_sum, sum_of_empty_and_not_empty_values) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    // both terms are positive
    int flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x1234567};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_sum(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // second term is positive, first one is negative
    flag = lil_sum(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // both terms are negative
    a.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_sum(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_sum, sum_of_two_equal_values_of_the_same_size) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    // both terms are positive
    int flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x2468ace};
    uint64_t empty_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, empty_arr, c.size);
    // second term is positive, first one is negative
    flag = lil_sum(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, empty_arr, c.size);
    // both terms are negative
    a.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_sum, sum_of_two_equal_values_of_different_size) {
    uint64_t arr_a[LIL_256_BIT - 1] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT - 1};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    // both terms are positive
    int flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x2468ace};
    uint64_t empty_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, empty_arr, c.size);
    // second term is positive, first one is negative
    flag = lil_sum(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, empty_arr, c.size);
    // both terms are negative
    a.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_sum, sum_of_two_unequal_values_of_the_same_size) {
    uint64_t arr_a[LIL_256_BIT] = {0x0123456776543210, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, 0};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    // both terms are positive
    int flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x012345677654320f, UINT64_MAX, 0, 1};
    uint64_t diff_arr[LIL_256_BIT] = {0xfedcba9889abcdef, 0, UINT64_MAX, 1};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, diff_arr, c.size);
    // second term is positive, first one is negative
    b.sign = LIL_PLUS; a.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, diff_arr, c.size);
    // both terms are negative
    b.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_sum, sum_of_two_unequal_values_of_different_size) {
    uint64_t arr_a[LIL_256_BIT] = {0x0123456776543210, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT - 1] = {UINT64_MAX, UINT64_MAX, UINT64_MAX};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT - 1};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    // both terms are positive
    int flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x012345677654320f, UINT64_MAX, 0, 1};
    uint64_t diff_arr[LIL_256_BIT] = {0xfedcba9889abcdef, 0, UINT64_MAX, 1};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    // first term is positive, second one is negative
    b.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, diff_arr, c.size);
    // second term is positive, first one is negative
    b.sign = LIL_PLUS; a.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, diff_arr, c.size);
    // both terms are negative 
    b.sign = LIL_MINUS;
    flag = lil_sum(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}
