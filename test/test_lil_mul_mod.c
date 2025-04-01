#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_mul_mod, multiplication_of_empty_values) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_mul_mod(&c, &a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

void fork_test_lil_mul_mod(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_b[LIL_256_BIT - 1] = {1};
        uint64_t arr_m[LIL_256_BIT] = {0x1234567};
        uint64_t arr_c[LIL_256_BIT + 2] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT - 1};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        long_int c = {PLUS, arr_c, LIL_256_BIT + 2};
        lil_mul_mod(&c, &a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_mul_mod, invalid_sized_terms_modulo_multiplication) {
    int status;
    fork_test_lil_mul_mod();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_mul_mod_zero(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX};
        uint64_t arr_b[LIL_256_BIT] = {1};
        uint64_t arr_m[LIL_256_BIT] = {0};
        uint64_t arr_c[LIL_256_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        long_int c = {PLUS, arr_c, LIL_256_BIT};
        lil_mul_mod(&c, &a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_mul_mod, zero_modulus_multiplication) {
    int status;
    fork_test_lil_mul_mod_zero();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_mul_mod, excessive_length_terms_modulo_multiplication) {
    uint64_t arr_a[LIL_256_BIT] = {0x0123456789abcdef, 0x123456789};
    uint64_t arr_b[LIL_256_BIT] = {0xfedabc9876543210, 0x123456789};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_mul_mod(&c, &a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x6d4259};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_mul_mod(&c, &b, &a, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}

Test(test_lil_mul_mod, modulo_multiplication) {
    uint64_t arr_a[LIL_256_BIT] = {0x0123456789abcdef, 0x987654321};
    uint64_t arr_b[LIL_256_BIT] = {0xfedabc9876543210, 0x123456789};
    uint64_t arr_m[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX};
    uint64_t arr_c[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    int flag = lil_mul_mod(&c, &a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0xb5722ac6313ff166, 0x456639bbdeaf94ff};
    cr_expect_arr_eq(c.val, expected_arr, c.size);
    flag = lil_mul_mod(&c, &b, &a, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c.sign, LIL_PLUS);
    cr_expect_arr_eq(c.val, expected_arr, c.size);
}
