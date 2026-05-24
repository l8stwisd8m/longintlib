#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void fork_negative_value_log(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {1};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {MINUS, arr_b, LIL_256_BIT};
        lil_log2(&a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_log2, negative_value_log) {
    int status;
    fork_negative_value_log();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

void fork_log_of_value_equal_to_null(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        uint64_t arr_b[LIL_256_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        long_int b = {PLUS, arr_b, LIL_256_BIT};
        lil_log2(&a, &b);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_log2, log_of_value_equal_to_null) {
    int status;
    fork_log_of_value_equal_to_null();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_log2, log_of_value_equal_to_one) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_log2(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_log2, log_of_value_equal_to_power_of_two) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {64};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_log2(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {6};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_log2, log_of_value_not_equal_to_power_of_two) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    uint64_t arr_b[LIL_256_BIT] = {0x1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    long_int b = {PLUS, arr_b, LIL_256_BIT};
    int flag = lil_log2(&a, &b);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {24};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
