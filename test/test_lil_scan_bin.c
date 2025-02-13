#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "test_utils.h"
#define BUFSIZE 128

void test_subroutine(lil_t *a, char *path, char *msg) {
    printf("%s", msg);
    FILE *fptr = freopen(path, "r", stdin);
    if (fptr == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    lil_scan_bin(a);
    fclose(fptr);
    stdin = stdin;
    printf("Input:\t");
    lil_print_bin(a);
}

void concatenation(char *path, const char *prefix, const char *beginning, const char *middle, const char *end) {
    snprintf(path, BUFSIZE, "%s%s%s%s", prefix, beginning, middle, end);
}

void test_scan_bin(lil_t *a) {
    const char *prefixes[] = { "", "minus_", "prefix_", "minus_prefix_" };
    const char *beginnings[] = { "zero_", "empty_", "leading_zero_", "single_digit_" };
    const char *msg_prefixes[] = { "", "negative ", "prefixed ", "negative prefixed " };
    const char *msg_beginnings[] = { "zero ", "empty ", "leading zero ", "single digit " };
    const char dir[] = "/home/siegfried/c/longintlib/test/assets/bin/"; // change to absolute path if it doesn't work
    const char input[] = "input.txt\0";
    const char msg_input[] = "Input of ";
    const char msg_end[] = "file \n";
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char *path = (char *)calloc(BUFSIZE, sizeof(char));
            char *msg = (char *)calloc(BUFSIZE, sizeof(char));
            concatenation(path, dir, prefixes[i], beginnings[j], input);
            concatenation(msg, msg_input, msg_prefixes[i], msg_beginnings[j], msg_end);
            test_subroutine(a, path, msg);
            free(path);
            free(msg);
        }
    }
}

int main(int argc, char *argv[]) {
    // binary scan test
    uint64_t arr_a[2] = {0};
    long_int a = {PLUS, arr_a, 2};
    
    printf("Binary input test \n");
    
    test_scan_bin(&a);
    return 0;
}
