#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

void fork_test_lil_sum_mod_zero_modulus(void) {
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
        lil_sum_mod(&a, &b, &c, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_sum_mod, invalid_zero_modulus) {
    int status;
    fork_test_lil_sum_mod_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_sum_mod_invalid_terms(void) {
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
        lil_sum_mod(&a, &b, &c, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_sum_mod, invalid_sized_terms_modulus) {
    int status;
    fork_test_lil_sum_mod_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_sum_mod, modulus_sum_of_positive_values_less_than_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x5440402c3d9ca120, 0x00497953bad573c0};
    uint64_t arr_c[LIL_256_BIT] = {0xcac9a44af6fcc9a8, 0x0dcdf4c3532b5114};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_sum_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x0000000000615778};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sum_mod, modulus_sum_of_negative_values_less_than_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0xcc29fa452034d79d};
    uint64_t arr_c[LIL_256_BIT] = {0xdb2c712a48633832, 0xd9002e56afc4556c, 0x0000000000256cb4};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {MINUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_sum_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x000000000081601e};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sum_mod, modulus_sum_of_values_equal_to_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0x1234567};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_sum_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sum_mod, modulus_sum_of_unequal_values) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0xc6dd927d89c3970c, 0x0000001104953f79};
    uint64_t arr_c[LIL_256_BIT] = {0x8efb124a376556eb, 0x00000480ae53bbc6};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_sum_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x000000000110a5ef};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
