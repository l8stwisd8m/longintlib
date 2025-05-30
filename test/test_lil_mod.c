#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_mod, modulus_of_an_empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_mod(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

void fork_test_lil_mod_zero_modulus(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_b[LIL_256_BIT] = {0};
        uint64_t arr_c[LIL_256_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT};
        long_int c = {PLUS, arr_c, LIL_256_BIT};
        lil_mod(&c, &a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_mod, invalid_zero_modulus) {
    int status;
    fork_test_lil_mod_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_mod_invalid_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT + 1] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_b[LIL_256_BIT - 1] = {0x1234567};
        uint64_t arr_c[LIL_256_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT + 1};
        long_int b = {PLUS, arr_b, LIL_256_BIT - 1};
        long_int c = {PLUS, arr_c, LIL_256_BIT};
        lil_mod(&c, &a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_mod, invalid_sized_terms_modulus) {
    int status;
    fork_test_lil_mod_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_mod, modulus_of_two_equal_terms) {
    uint64_t arr_a[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_mod(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_mod, modulus_of_two_unequal_terms) {
    uint64_t arr_a[LIL_256_BIT] = {0xfedcba9876543210, UINT64_MAX, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_mod(&c, &a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x000000000098042c};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_mod(&c, &b, &a);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t new_arr[LIL_256_BIT] = {0x1234567};
    cr_expect_arr_eq(c.val, new_arr, c.size);
}
