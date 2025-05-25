#include <stdint.h>
#include <limits.h>
#include <iso646.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

void fork_test_lil_str_bin(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_128_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_128_BIT};
        char str[] = "0b000xyz";
        lil_str_bin(&a, str);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_str_bin, invalid_input) {
    int status;
    fork_test_lil_str_bin();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_str_bin, excessive_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0000000000000000000101";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {5};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, minus_empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, minus_leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-000101";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {5};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, minus_prefix_empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0b";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, minus_prefix_leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0b000101";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {5};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, minus_prefix_single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0b1";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, minus_prefix_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0b0";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, minus_single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-1";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, minus_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, prefix_empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0b";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, prefix_leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0b000101";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {5};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, prefix_single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0b1";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, prefix_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0b0";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "1";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_bin, zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {MINUS, arr_a, LIL_128_BIT};
    char str[] = "0";
    int flag = lil_str_bin(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
