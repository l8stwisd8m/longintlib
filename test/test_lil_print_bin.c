#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <iso646.h>
#include <criterion/criterion.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#define BUF_SIZE 512

void test_lil_print_bin_asset_gen(lil_t *src, const char *path) {
    // write an output of a function to asset file located in path
    
    const char *output_dir = getenv("OUTPUT_DIR");
    if (!output_dir) {
        fprintf(stderr, "OUTPUT_DIR environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    
    char file_path[BUF_SIZE];
    snprintf(file_path, sizeof(file_path), "%s%s", output_dir, path);
    
    FILE *file = fopen(file_path, "w");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    FILE *original_stdout = stdout;
    stdout = file;
    lil_print_bin(src);
    stdout = original_stdout;
    fclose(file);
}

int test_lil_print_bin_asset_check(const char *str, const char *path) {
    // compare given string with recieved from path one; both should be terminated by '\n'
    
    const char *output_dir = getenv("OUTPUT_DIR");
    if (!output_dir) {
        fprintf(stderr, "OUTPUT_DIR environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    
    char file_path[BUF_SIZE];
    snprintf(file_path, sizeof(file_path), "%s%s", output_dir, path);
    
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    char recieved_str[BUF_SIZE];
    fgets(recieved_str, sizeof(recieved_str), file);
    fclose(file);
    
    int flag = 0;
    for (int i = 0; i < BUF_SIZE; i++) {
        if ((str[i] == '\n') or (recieved_str[i] == '\n')) break;
        if (str[i] != recieved_str[i]) {
            flag = 1;
            break;
        }
    }
    return flag;
}

Test(test_lil_print_bin, positive_empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/positive_empty_value.txt";
    test_lil_print_bin_asset_gen(&a, path);
    const char expected_str[] = "0b 0000000000000000000000000000000000000000000000000000000000000000 0000000000000000000000000000000000000000000000000000000000000000 0000000000000000000000000000000000000000000000000000000000000000 0000000000000000000000000000000000000000000000000000000000000000\n";
    int flag = test_lil_print_bin_asset_check(expected_str, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_print_bin, negative_empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/negative_empty_value.txt";
    test_lil_print_bin_asset_gen(&a, path);
    const char expected_str[] = "0b 0000000000000000000000000000000000000000000000000000000000000000 0000000000000000000000000000000000000000000000000000000000000000 0000000000000000000000000000000000000000000000000000000000000000 0000000000000000000000000000000000000000000000000000000000000000\n";
    int flag = test_lil_print_bin_asset_check(expected_str, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_print_bin, positive_nonzero_value) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/positive_nonzero_value.txt";
    test_lil_print_bin_asset_gen(&a, path);
    const char expected_str[] = "0b 1111111111111111111111111111111111111111111111111111111111111111 1111111111111111111111111111111111111111111111111111111111111111 1111111111111111111111111111111111111111111111111111111111111111 1111111111111111111111111111111111111111111111111111111111111111\n";
    int flag = test_lil_print_bin_asset_check(expected_str, path);
    cr_expect_eq(flag, 0);
}

Test(test_lil_print_bin, negative_nonzero_value) {
    uint64_t arr_a[LIL_256_BIT] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
    long_int a = {MINUS, arr_a, LIL_256_BIT};
    const char path[] = "bin/negative_nonzero_value.txt";
    test_lil_print_bin_asset_gen(&a, path);
    const char expected_str[] = "-0b 1111111111111111111111111111111111111111111111111111111111111111 1111111111111111111111111111111111111111111111111111111111111111 1111111111111111111111111111111111111111111111111111111111111111 1111111111111111111111111111111111111111111111111111111111111111\n";
    int flag = test_lil_print_bin_asset_check(expected_str, path);
    cr_expect_eq(flag, 0);
}
