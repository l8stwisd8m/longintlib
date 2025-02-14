#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "test_utils.h"
#define BUFSIZE 100

void test_subroutine(lil_t *a, char *path, char *msg) {
    printf("%s", msg);
    FILE *fptr = freopen(path, "r", stdin);
    if (fptr == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    lil_scan_dec(a);
    fclose(fptr);
    stdin = stdin;
    printf("Input:\t");
    lil_print_dec(a);
}

void concatenation(char *path, const char *beginning, const char *middle, const char *end) {
    snprintf(path, BUFSIZE, "%s%s%s", beginning, middle, end);
}

void test_scan_dec(lil_t *a) {
    const char *prefixes[] = { "zero_", "empty_", "leading_zero_", "single_digit_" };
    const char *msg_prefixes[] = { "zero ", "empty ", "leading zero ", "single digit " };
    const char dir[] = "/home/siegfried/c/longintlib/test/assets/dec/"; // change to absolute path if it doesn't work
    const char input[] = "input.txt\0";
    const char msg_input[] = "Input of ";
    const char msg_end[] = "file \n";
    
    for (int i = 0; i < 4; i++) {
        char *path = (char *)calloc(BUFSIZE, sizeof(char));
        char *msg = (char *)calloc(BUFSIZE, sizeof(char));
        concatenation(path, dir, prefixes[i], input);
        concatenation(msg, msg_input, msg_prefixes[i], msg_end);
        test_subroutine(a, path, msg);
        free(path);
        free(msg);
    }
    
    const char new_dir[] = "/home/siegfried/c/longintlib/test/assets/dec/minus_"; // change to absolute path if it doesn't work
    const char new_msg_input[] = "Input of negative ";
     
    for (int i = 0; i < 4; i++) {
        char *path = (char *)calloc(BUFSIZE, sizeof(char));
        char *msg = (char *)calloc(BUFSIZE, sizeof(char));
        concatenation(path, new_dir, prefixes[i], input);
        concatenation(msg, new_msg_input, msg_prefixes[i], msg_end);
        test_subroutine(a, path, msg);
        free(path);
        free(msg);
    }
}

int main(int argc, char *argv[]) {
    // decimal scan test
    uint64_t arr_a[N] = {0};
    long_int a = {PLUS, arr_a, N};
    
    printf("Decimal input test \n");
    
    test_scan_dec(&a);
    return 0;
}
