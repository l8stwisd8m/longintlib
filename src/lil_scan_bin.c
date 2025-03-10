#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include <stdbool.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

int lil_scan_bin(lil_t *src) {
    // scan binary representation of source
    
    bool sign_check = true; // true when "sign input" check is required
    bool prefix_check = true; // true when "prefix input" check is required
    bool leading_zero_check = true; // true when "leading zero(es) check" is required
    bool prefix_condition = false; // condition for "prefix input" check
    
    const uint64_t lim = LIL_BASE * src->size;
    uint64_t ctr = 0;
    char ch = 0;
    
    // default input
    src->sign = LIL_PLUS;
    LIL_SET_NULL(src);

    while (ctr <= lim) {
        ch = getchar();
        
        // check termination symbols
        if ((ch == '\n') or (ch == '\0') or (ch == EOF) or feof(stdin)) break;
        
        // condition to stop or continue prefix input check
        if ((ch == '0') and (not sign_check) and leading_zero_check) {
            if (prefix_check) prefix_condition = true; // continue "prefix input" check
            else prefix_condition = false; // stop "prefix input" check
        }
        
        // condition to stop "leading zero(es) input" check after other checks (if it's enabled)
        if ((ch != '0') and (not sign_check) and leading_zero_check) {
            if (prefix_condition) {
                leading_zero_check = true; // continue "leading zero(es) input" check
                prefix_check = true; // continue "prefix input" check
            }
            else {
                leading_zero_check = false; // stop "leading zero(es) input" check
                prefix_check = false; // stop "prefix input" check
            }
        }
        
        // first symbol input
        if (sign_check) {
            if (ch == '-') {
                src->sign = LIL_MINUS;
                leading_zero_check = true; // continue "leading zero(es) input" check
            }
            if (ch == '0') {
                prefix_condition = true; // condition for "prefix input" check
                leading_zero_check = true; // continue "leading zero(es) input" check
            }
            if (ch == '1') {
                prefix_check = false; // stop "prefix input" check
                leading_zero_check = false; // stop "leading zero(es) input" check
            }
            sign_check = false; // stop "sign input" check
        }
        
        // prefix input 
        if (prefix_condition and prefix_check) {
            if (ch == 'b') prefix_condition = false;
            prefix_check = false; // stop "prefix input" check
        }
        
        // digit input 
        if ((not sign_check) and (not prefix_check) and (not leading_zero_check)) {
            if ((ch != '0') and (ch != '1')) {
                errno = ERR_INVALID_INPUT;
                perror("An invalid character entered");
                exit(EXIT_FAILURE);
            }
            assert((ch == '0') or (ch == '1'));
            lil_shl(src);
            src->val[0] = src->val[0] | (uint64_t)(ch - '0');
            ctr += 1;
        }
    }
    
    // correct result sign
    if (lil_is_null(src)) src->sign = LIL_PLUS;
    return 0;
}
