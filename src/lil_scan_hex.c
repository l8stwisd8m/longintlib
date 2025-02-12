#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include <stdbool.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

void lil_scan_hex(lil_t *src) {
    // scan hexadecimal representation of source
    
    bool sign_check = true; // true when "sign input" check is required
    bool prefix_check = true; // true when "prefix input" check is required
    bool leading_zero_check = true; // true when "leading zero(es) check" is required
    bool prefix_condition = false; // condition for "prefix input" check
    
    const uint64_t lim = LIL_BASE * src->size;
    uint64_t ctr = 0;
    char ch = 0;
    
    // default input
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
            if ((ch == 'x') or (ch == 'X')) prefix_condition = false;
            prefix_check = false; // stop "prefix input" check
        }
        
        // digit input 
        if ((not sign_check) and (not prefix_check) and (not leading_zero_check)) {
            lil_shln(src, 4);
            ctr += 4;
            switch(ch) {
                case '0':
                    src->val[0] = src->val[0] | (uint64_t)0x0;
                    break;
                case '1':
                    src->val[0] = src->val[0] | (uint64_t)0x1;
                    break;
                case '2':
                    src->val[0] = src->val[0] | (uint64_t)0x2;
                    break;
                case '3':
                    src->val[0] = src->val[0] | (uint64_t)0x3;
                    break;
                case '4':
                    src->val[0] = src->val[0] | (uint64_t)0x4;
                    break;
                case '5':
                    src->val[0] = src->val[0] | (uint64_t)0x5;
                    break;
                case '6':
                    src->val[0] = src->val[0] | (uint64_t)0x6;
                    break;
                case '7':
                    src->val[0] = src->val[0] | (uint64_t)0x7;
                    break;
                case '8':
                    src->val[0] = src->val[0] | (uint64_t)0x8;
                    break;
                case '9':
                    src->val[0] = src->val[0] | (uint64_t)0x9;
                    break;
                case 'a':
                    src->val[0] = src->val[0] | (uint64_t)0xa;
                    break;
                case 'b':
                    src->val[0] = src->val[0] | (uint64_t)0xb;
                    break;
                case 'c':
                    src->val[0] = src->val[0] | (uint64_t)0xc;
                    break;
                case 'd':
                    src->val[0] = src->val[0] | (uint64_t)0xd;
                    break;
                case 'e':
                    src->val[0] = src->val[0] | (uint64_t)0xe;
                    break;
                case 'f':
                    src->val[0] = src->val[0] | (uint64_t)0xf;
                    break;
                case 'A':
                    src->val[0] = src->val[0] | (uint64_t)0xa;
                    break;
                case 'B':
                    src->val[0] = src->val[0] | (uint64_t)0xb;
                    break;
                case 'C':
                    src->val[0] = src->val[0] | (uint64_t)0xc;
                    break;
                case 'D':
                    src->val[0] = src->val[0] | (uint64_t)0xd;
                    break;
                case 'E':
                    src->val[0] = src->val[0] | (uint64_t)0xe;
                    break;
                case 'F':
                    src->val[0] = src->val[0] | (uint64_t)0xf;
                    break;
                default:
                    assert(false and "invalid character");
            }
        }
    }
    
    // correct result sign
    if (lil_is_null(src)) src->sign = LIL_PLUS;
}
