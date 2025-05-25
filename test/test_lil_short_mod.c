#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_short_mod, short_modulus_of_an_empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    uint64_t c = 0;
    int flag = lil_short_mod(&c, &a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c, (uint64_t)0);
}

void fork_test_lil_short_mod_zero_modulus(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        uint64_t b = 0;
        uint64_t c = 0;
        lil_short_mod(&c, &a, b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_short_mod, invalid_zero_short_modulus) {
    int status;
    fork_test_lil_short_mod_zero_modulus();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_short_mod, modulus_of_two_equal_terms) {
    uint64_t arr_a[LIL_256_BIT] = {0x1234567};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    uint64_t c = 0;
    int flag = lil_short_mod(&c, &a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c, (uint64_t)0);
}

Test(test_lil_short_mod, short_modulus_of_two_unequal_terms) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    uint64_t b = 0x1234567;
    uint64_t c = 0;
    int flag = lil_short_mod(&c, &a, b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(c, (uint64_t)0x529e8d);
}
