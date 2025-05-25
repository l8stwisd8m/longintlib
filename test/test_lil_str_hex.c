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

void fork_test_lil_str_hex(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_128_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_128_BIT};
        char str[] = "0x000xyz";
        lil_str_hex(&a, str);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_str_hex, invalid_input) {
    int status;
    fork_test_lil_str_hex();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_str_hex, excessive_input) {
    uint64_t arr_a[LIL_128_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0123456789abcdef0123456789ABCDEF0123456789abcdef";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0x0123456789abcdef, 0x0123456789abcdef};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0000000000000000000abc";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {2748};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, minus_empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, minus_leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-000abc";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {2748};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, minus_prefix_empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0x";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, minus_prefix_leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0x000abc";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {2748};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, minus_prefix_single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0xa";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {10};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, minus_prefix_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0x0";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, minus_single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-A";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_128_BIT] = {10};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, minus_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "-0";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, prefix_empty_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0x";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, prefix_leading_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0x000abc";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {2748};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, prefix_single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0xa";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {10};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, prefix_zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "0x0";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, single_digit_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_128_BIT};
    char str[] = "A";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {10};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_str_hex, zero_input) {
    uint64_t arr_a[LIL_128_BIT] = {UINT64_MAX, UINT64_MAX};
    long_int a = {MINUS, arr_a, LIL_128_BIT};
    char str[] = "0";
    int flag = lil_str_hex(&a, str);
    cr_expect_eq(flag, 0);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_128_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
