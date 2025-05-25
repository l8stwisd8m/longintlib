#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <iso646.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"
#define BUF_SIZE 512

int test_lil_scan_bin_asset_check(lil_t *exp, const char *path) {
    // compare given long integer with recieved from path one
    
    const char *output_dir = getenv("INPUT_DIR");
    if (!output_dir) {
        fscanf(stderr, "OUTPUT_DIR environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    
    char file_path[BUF_SIZE];
    snprintf(file_path, sizeof(file_path), "%s%s", output_dir, path);
    
    FILE *original_stdin = stdin;
    FILE *file = freopen(file_path, "r", stdin);
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    long_int *src;
    LIL_MALLOC(src, LIL_256_BIT);
    lil_scan_bin(src);
    fclose(file);
    stdin = original_stdin;
    
    int flag = lil_cmp(src, exp);
    LIL_FREE(src);
    return flag;
}

void fork_test_lil_scan_bin(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        const char path[] = "bin/invalid_input.txt";
        test_lil_scan_bin_asset_check(&a, path);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_scan_bin, invalid_input) {
    int status;
    fork_test_lil_scan_bin();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_scan_bin, excessive_input) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/excessive_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, empty_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/empty_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, leading_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {5};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/leading_zero_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, minus_empty_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/minus_empty_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, minus_leading_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {5};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/minus_leading_zero_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, minus_prefix_empty_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/minus_prefix_empty_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, minus_prefix_leading_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {5};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/minus_prefix_leading_zero_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, minus_prefix_single_digit_input) {
    uint64_t arr_a[LIL_256_BIT] = {1};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/minus_prefix_single_digit_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, minus_prefix_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/minus_prefix_zero_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, minus_single_digit_input) {
    uint64_t arr_a[LIL_256_BIT] = {1};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/minus_single_digit_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, minus_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/minus_zero_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, prefix_empty_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/prefix_empty_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, prefix_leading_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {5};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/prefix_leading_zero_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, prefix_single_digit_input) {
    uint64_t arr_a[LIL_256_BIT] = {1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/prefix_single_digit_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, prefix_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/prefix_zero_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, single_digit_input) {
    uint64_t arr_a[LIL_256_BIT] = {1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/single_digit_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_bin, zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/zero_input.txt";
    int flag = test_lil_scan_bin_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}
