#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

Test(test_lil_add, same_sized_terms_addition) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, 0, UINT64_MAX, 0};
    uint64_t arr_b[LIL_256_BIT] = {0, UINT64_MAX, UINT64_MAX, 0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_add(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX - 1, 1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_add, overflow_while_addition) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_add(&a, &b);
    cr_expect_eq(flag, LIL_OVERFLOW);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_add, valid_different_sized_terms_addition) {
    uint64_t arr_a[LIL_256_BIT + 1] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    uint64_t arr_b[LIL_256_BIT] = {1};
    long_int a = {PLUS, arr_a, LIL_256_BIT + 1};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_add(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT + 1] = {0, 0, 0, 0, 1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

void fork_test_lil_add(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
        uint64_t arr_b[LIL_256_BIT + 1] = {1};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT + 1};
        lil_add(&a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_add, invalid_different_sized_terms_addition) {
    int status;
    fork_test_lil_add();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}
