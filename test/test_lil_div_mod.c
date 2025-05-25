#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

void fork_test_lil_div_mod_zero_modulus(void) {
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
        lil_div_mod(&a, &b, &c, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_div_mod, invalid_zero_modulus) {
    int status;
    fork_test_lil_div_mod_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_test_lil_div_mod_invalid_terms(void) {
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
        lil_div_mod(&a, &b, &c, &m);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_div_mod, invalid_sized_terms_modulus) {
    int status;
    fork_test_lil_div_mod_invalid_terms();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_div_mod, modulo_division_of_positive_values_less_than_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x1fec43317ed71302, 0xa894f6609962e544, 0x000a4acad6635e40};
    uint64_t arr_c[LIL_256_BIT] = {0x05d720dc486c8d06, 0x841db2cb1127bafe, 0x0012ee629d721324};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_div_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x000000000071676b};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_div_mod, modulo_division_of_negative_values_less_than_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x9e574b6072fdeb22, 0x00002818f933edfa};
    uint64_t arr_c[LIL_256_BIT] = {0x449f51750fd06638, 0x00000908efe05558};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {MINUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_div_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x00000000011ee22e};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_div_mod, modulo_division_of_values_equal_to_modulus) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    uint64_t arr_c[LIL_256_BIT] = {0x1234};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_div_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_div_mod, modulo_division_of_unequal_values) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x8da6307a9d390b8c, 0x000000003b4ab78c};
    uint64_t arr_c[LIL_256_BIT] = {0x6d7217ca9fffffff, 0x00000001431e0fae};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_div_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x000000000103bef0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_div_mod, modulo_division_by_one) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x8da6307a9d390b8c, 0x000000003b4ab78c};
    uint64_t arr_c[LIL_256_BIT] = {1};
    uint64_t arr_m[LIL_256_BIT] = {0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    long_int c = {PLUS, arr_c, LIL_256_BIT};
    long_int m = {PLUS, arr_m, LIL_256_BIT};
    int flag = lil_div_mod(&a, &b, &c, &m);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_PLUS);
    uint64_t expected_arr[LIL_256_BIT] = {0x1054cf7};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
