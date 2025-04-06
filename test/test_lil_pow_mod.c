#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void fork_test_lil_pow_mod_zero_modulus(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {21};
        uint64_t arr_c[LIL_256_BIT] = {12};
        uint64_t arr_m[LIL_256_BIT] = {0};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT};
        long_int c = {PLUS, arr_c, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_pow_mod(&a, &b, &c, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_pow_mod, invalid_zero_modulus) {
    int status;
    fork_test_lil_pow_mod_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_pow_mod_invalid_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT + 1] = {21};
        uint64_t arr_c[LIL_256_BIT - 1] = {12};
        uint64_t arr_m[LIL_256_BIT] = {0x1234567};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT + 1};
        long_int c = {PLUS, arr_c, LIL_256_BIT - 1};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_pow_mod(&a, &b, &c, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_pow_mod, invalid_sized_terms_modulus) {
    int status;
    fork_test_lil_pow_mod_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_pow_mod, modulus_power_of_positive_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0xa0ea31cd4546e6c8, 0x9ea58344ff1db5ba, 0x00000017a6fd31b9};
    uint64_t arr_c[LIL_256_BIT] = {0x7ec53f9d73d333d7, 0x000016857883e980};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_pow_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x0000000000844f3e};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_pow_mod, modulus_power_of_negative_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x7a9d6f7bac2cb085, 0xe8281f815ce44d50, 0x00000000003c7b06};
    uint64_t arr_c[LIL_256_BIT] = {0x7ec53f9d73d333d7, 0x000016857883e980};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {MINUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_pow_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x00000000011fec24};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_pow_mod, modulus_power_of_value_equal_to_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0x1234};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_pow_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_pow_mod, modulus_raising_to_the_power_of_one) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0xfc18ee68ea3ad982, 0x00000000009799f8};
    uint64_t arr_c[LIL_256_BIT] = {1};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_pow_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x00000000003e4d8e};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_pow_mod, modulus_raising_to_the_power_of_zero) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0xce1cc1724ac5aacb, 0x0000000000012320};
    uint64_t arr_c[LIL_256_BIT] = {0};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_pow_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
