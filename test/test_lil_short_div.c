#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_short_div, short_division_of_an_empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_short_div(&c, &a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

void fork_test_lil_short_div_zero_division(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_c[LIL_256_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        uint64_t b = 0;
        long_int c = {PLUS, arr_c, LIL_256_BIT};
        lil_short_div(&c, &a, b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_short_div, invalid_zero_short_division) {
    int status;
    fork_test_lil_short_div_zero_division();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_short_div_invalid_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT + 1] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_c[LIL_256_BIT - 1] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT + 1};
        uint64_t b = 0x1234567;
        long_int c = {PLUS, arr_c, LIL_256_BIT - 1};
        lil_short_div(&c, &a, b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_short_div, invalid_sized_terms_short_division) {
    int status;
    fork_test_lil_short_div_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_short_div, division_of_two_equal_terms) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_short_div(&c, &a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_256_BIT] = {1};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_short_div, short_division_of_two_unequal_terms) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_short_div(&c, &a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_MINUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x859be40c26aec9be, 0x3ac6d58fc7faf0f5, 0x0032441117c22c14, 0x000000e100006a59};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}
