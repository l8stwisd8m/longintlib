#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_gcd, gcd_of_not_empty_value_and_zero) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT] = {0};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_gcd(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x1234567};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_gcd(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

void fork_test_lil_gcd_empty_values(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {0};
        uint64_t arr_c[LIL_256_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT};
        long_int c = {PLUS, arr_c, LIL_256_BIT};
        lil_gcd(&c, &a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_gcd, gcd_of_two_empty_values) {
    int status;
    fork_test_lil_gcd_empty_values();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_gcd, gcd_of_two_short_equal_values) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_gcd(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x1234567};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_gcd, gcd_of_two_short_unequal_values) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_gcd(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {1};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_gcd, gcd_of_short_and_long_values) {
    uint64_t arr_a[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_gcd(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {1};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_gcd(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_gcd, gcd_of_two_long_equal_values) {
    uint64_t arr_a[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_gcd(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_gcd(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_gcd, gcd_of_two_long_unequal_values) {
    uint64_t arr_a[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_gcd(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0xf0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_gcd(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}
