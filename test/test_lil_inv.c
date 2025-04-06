#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void fork_test_lil_inv_zero_value(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {0};
        uint64_t arr_m[LIL_256_BIT] = {0x1234567};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_inv(&a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_inv, invalid_zero_value) {
    int status;
    fork_test_lil_inv_zero_value();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_inv_zero_modulus(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {0x1234567};
        uint64_t arr_m[LIL_256_BIT] = {0};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int b = {MINUS, arr_b, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_inv(&a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_inv, invalid_zero_modulus) {
    int status;
    fork_test_lil_inv_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_inv_invalid_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT - 1] = {0};
        uint64_t arr_b[LIL_256_BIT + 1] = {UINT64_MAX};
        uint64_t arr_m[LIL_256_BIT] = {0x1234567};
        long_int a = {MINUS, arr_a, LIL_256_BIT - 1};
        long_int b = {MINUS, arr_b, LIL_256_BIT + 1};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_inv(&a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_inv, invalid_sized_terms_modulus) {
    int status;
    fork_test_lil_inv_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_inv_invalid_not_coprime_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {0xc362968e5fbb4cfd, 0x000000000000aee6};
        uint64_t arr_m[LIL_256_BIT] = {0x1bdf7ebad62c0398, 0xc5483f75b14d1801, 0x0000000005a3375e};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int b = {MINUS, arr_b, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_inv(&a, &b, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_inv, invalid_not_coprime_terms_inversion) {
    int status;
    fork_test_lil_inv_invalid_not_coprime_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_inv, modulo_inversion_of_negative_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0xb10b836038276e6c, 0x0000000003fd35ea};
    uint64_t arr_m[LIL_256_BIT] = {0x00007df2442fd271};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int m = {MINUS, arr_m, LIL_256_BIT};
    int flag = lil_inv(&a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x0000302537566b88};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_inv, modulo_inversion_of_positive_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0xa4b7e7352c66a1a1, 0x00edc4e55287585f};
    uint64_t arr_m[LIL_256_BIT] = {0x9d9bff9e34b1a968, 0x000079480bda89d9};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_inv(&a, &b, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0xf5fbf653998fdca1, 0x0000239417a018cc};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
