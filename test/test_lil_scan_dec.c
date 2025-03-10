#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <iso646.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"
#define BUF_SIZE 512

int test_lil_scan_dec_asset_check(lil_t *exp, const char *path) {
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
    lil_scan_dec(src);
    fclose(file);
    stdin = original_stdin;
    
    int flag = lil_cmp(src, exp);
    LIL_FREE(src);
    return flag;
}

void fork_test_lil_scan_dec(void) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        uint64_t arr_a[LIL_256_BIT] = {0};
        long_int a = {PLUS, arr_a, LIL_256_BIT};
        const char path[] = "dec/invalid_input.txt";
        test_lil_scan_dec_asset_check(&a, path);
        exit(EXIT_SUCCESS); // default exit status if the function didn't crashed
    }
}

Test(test_lil_scan_dec, invalid_input) {
    int status;
    fork_test_lil_scan_dec();
    wait(&status);
    if(WEXITSTATUS(status) == EXIT_FAILURE) cr_assert(1);
    else cr_assert_fail();
}

Test(test_lil_scan_dec, empty_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/empty_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_dec, leading_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/leading_zero_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_dec, minus_empty_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/minus_empty_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_dec, minus_leading_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/minus_leading_zero_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_dec, minus_single_digit_input) {
    uint64_t arr_a[LIL_256_BIT] = {5};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/minus_single_digit_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_dec, minus_zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/minus_zero_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_dec, single_digit_input) {
    uint64_t arr_a[LIL_256_BIT] = {5};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/single_digit_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_dec, zero_input) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/zero_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_scan_dec, excessive_input) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, 0xaa987b6e6fd29fff, 0x49ef0eb713f39ebe, 0xdd15fe86affad912};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "dec/excessive_input.txt";
    int flag = test_lil_scan_dec_asset_check(&a, path);
    cr_expect_eq(flag, 0);
}
