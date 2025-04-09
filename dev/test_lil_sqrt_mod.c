#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_sqrt_mod, invalid_zero_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int m = {MINUS, arr_m, LIL_256_BIT};
    int flag = lil_sqrt_mod(&a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ANSWER);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

void fork_test_lil_sqrt_mod_zero_modulus(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {0x1234567};
        uint64_t arr_m[LIL_256_BIT] = {0};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int b = {MINUS, arr_b, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_sqrt_mod(&a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_sqrt_mod, invalid_zero_modulus) {
    int status;
    fork_test_lil_sqrt_mod_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_sqrt_mod_invalid_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT - 1] = {0};
        uint64_t arr_b[LIL_256_BIT + 1] = {UINT64_MAX};
        uint64_t arr_m[LIL_256_BIT] = {0x1234567};
        long_int a = {MINUS, arr_a, LIL_256_BIT - 1};
        long_int b = {MINUS, arr_b, LIL_256_BIT + 1};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_sqrt_mod(&a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_sqrt_mod, invalid_sized_terms_modulus) {
    int status;
    fork_test_lil_sqrt_mod_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_sqrt_mod_invalid_not_coprime_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {123456};
        uint64_t arr_m[LIL_256_BIT] = {12345678};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int b = {MINUS, arr_b, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_sqrt_mod(&a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_sqrt_mod, invalid_not_coprime_terms_inversion) {
    int status;
    fork_test_lil_sqrt_mod_invalid_not_coprime_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_sqrt_mod, quadratic_nonresidue) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {123};
    uint64_t arr_m[LIL_256_BIT] = {1303};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int m = {MINUS, arr_m, LIL_256_BIT};
    int flag = lil_sqrt_mod(&a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ANSWER);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sqrt_mod, easy_case) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {1234};
    uint64_t arr_m[LIL_256_BIT] = {1303};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int m = {MINUS, arr_m, LIL_256_BIT};
    int flag = lil_sqrt_mod(&a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {799};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sqrt_mod, case_b_is_equal_to_one) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {123};
    uint64_t arr_m[LIL_256_BIT] = {1301};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int m = {MINUS, arr_m, LIL_256_BIT};
    int flag = lil_sqrt_mod(&a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {821};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sqrt_mod, case_b_is_not_equal_to_one) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {666};
    uint64_t arr_m[LIL_256_BIT] = {1301};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int m = {MINUS, arr_m, LIL_256_BIT};
    int flag = lil_sqrt_mod(&a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {943};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
