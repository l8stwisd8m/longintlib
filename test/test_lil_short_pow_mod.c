#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_short_pow_mod, short_modulus_power_of_an_empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    uint64_t n = 0x1234567;
    int flag = lil_short_pow_mod(&a, n, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

void fork_test_lil_short_pow_mod_zero_modulus(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0x1234567};
        uint64_t arr_m[LIL_256_BIT] = {0};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        uint64_t n = 0x1234567;
        lil_short_pow_mod(&a, n, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_short_pow_mod, invalid_zero_modulus) {
    int status;
    fork_test_lil_short_pow_mod_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_short_pow_mod_invalid_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT - 1] = {UINT64_MAX};
        uint64_t arr_m[LIL_256_BIT] = {0x1234567};
        long_int a = {MINUS, arr_a, LIL_256_BIT - 1};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        uint64_t n = 0x1234567;
        lil_short_pow_mod(&a, n, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_short_pow_mod, invalid_sized_terms_modulus_power) {
    int status;
    fork_test_lil_short_pow_mod_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_short_pow_mod, short_modulus_power_equal_to_zero) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    uint64_t n = 0;
    int flag = lil_short_pow_mod(&a, n, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_short_pow_mod, short_modulus_power_equal_to_one) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    uint64_t n = 1;
    int flag = lil_short_pow_mod(&a, n, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x3930};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_short_pow_mod, short_modulus_power_of_negative_value) {
    uint64_t arr_a[LIL_256_BIT] = {0x2336d7fbb70858d1, 0xb963ea7ab1e7a401, 0x000001e91d92a5c9};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    uint64_t n = 0x1234567;
    int flag = lil_short_pow_mod(&a, n, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x00000000006fe81d};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
