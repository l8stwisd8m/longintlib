#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void fork_test_lil_sqrt(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {1};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {MINUS, arr_b, LIL_256_BIT};
        lil_sqrt(&a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_sqrt, negative_value_sqrt) {
    int status;
    fork_test_lil_sqrt();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_sqrt, empty_value_sqrt) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_sqrt(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sqrt, sqrt_of_one) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_sqrt(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sqrt, sqrt_of_perfect_square) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {144};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_sqrt(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {12};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_sqrt, sqrt_of_value_not_equal_to_perfect_square) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {88};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_sqrt(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {9};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
