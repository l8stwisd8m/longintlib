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

void fork_test_lil_str_dec(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_128_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_128_BIT};
        char str[] = "000xyz";
        lil_str_dec(&a, str);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_str_dec, invalid_input) {
    int status;
    fork_test_lil_str_dec();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_str_dec, excessive_input) {
    uint64_t arr_a[LIL_128_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "6277101735386680763835789423207666416102355444464034512895";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0xffffffffffffffff, 0xffffffffffffffff};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_dec, empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_dec, leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0000000000000000000123456789";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {123456789};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_dec, minus_empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_dec, minus_leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-000123456789";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {123456789};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_dec, minus_single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-5";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {5};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_dec, minus_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_dec, single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "5";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {5};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_dec, zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {MINUS, arr_a, LIL_128_BIT};
    char str[] = "0";
    int flag = lil_str_dec(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
