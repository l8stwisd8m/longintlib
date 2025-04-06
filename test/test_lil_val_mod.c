#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_val_mod, modulus_of_an_empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_val_mod(&a, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

void fork_test_lil_val_mod_zero_modulus(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_m[LIL_256_BIT] = {0};
        long_int a = {MINUS, arr_a, LIL_256_BIT};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_val_mod(&a, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_val_mod, invalid_zero_modulus) {
    int status;
    fork_test_lil_val_mod_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_val_mod_invalid_terms(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT + 1] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_m[LIL_256_BIT] = {1};
        long_int a = {MINUS, arr_a, LIL_256_BIT + 1};
        long_int m = {PLUS, arr_m, LIL_256_BIT};
        lil_val_mod(&a, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_val_mod, invalid_sized_terms_modulus) {
    int status;
    fork_test_lil_val_mod_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_val_mod, modulus_of_positive_value) {
    uint64_t arr_a[LIL_256_BIT] = {0x2fe5c329b0b0b135, 0x5676b986676339fe, 0x0000000000231fd0};
    uint64_t arr_m[LIL_256_BIT] = {0x00000000075bcd15};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_val_mod(&a, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x00000000058a83d8};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_val_mod, modulus_of_negative_value) {
    uint64_t arr_a[LIL_256_BIT] = {0xf2e3b19f7c045f15, 0x0000000000661efd};
    uint64_t arr_m[LIL_256_BIT] = {0x000000000012d687};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_val_mod(&a, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x000000000009fe6a};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_val_mod, modulus_of_positive_value_less_than_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0x00000000075bcd15};
    uint64_t arr_m[LIL_256_BIT] = {0xacf2220158f19bdf, 0x0bfe9f28c0b7c287};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_val_mod(&a, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x00000000075bcd15};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_val_mod, modulus_of_negative_value_less_than_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0x00000000075bcd15};
    uint64_t arr_m[LIL_256_BIT] = {0x2089657ac242da7c, 0x00000000000761e6};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_val_mod(&a, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x2089657abae70d67, 0x00000000000761e6};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_val_mod, modulus_of_value_equal_to_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0x00000000075bcd15};
    uint64_t arr_m[LIL_256_BIT] = {0x00000000075bcd15};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_val_mod(&a, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
