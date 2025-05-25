#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_cpy, same_sized_terms_copy) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT};
    int flag = lil_cpy(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    cr_expect_eq(a.sign, LIL_MINUS);
    cr_expect_eq(a.size, b.size);
    cr_expect_arr_eq(a.val, b.val, b.size);
}

Test(test_lil_cpy, valid_different_sized_terms_copy) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT - 1] = {UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {MINUS, arr_b, LIL_256_BIT - 1};
    int flag = lil_cpy(&a, &b);
    cr_expect_eq(flag, LIL_TRUNCATED);
    cr_expect_eq(a.sign, LIL_MINUS);
    cr_expect_eq(a.size, b.size);
    cr_expect_arr_eq(a.val, b.val, b.size);
}

void fork_test_lil_cpy(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT + 1] = {1};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT + 1};
        lil_cpy(&a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_cpy, invalid_different_sized_terms_copy) {
    int status;
    fork_test_lil_cpy();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}
