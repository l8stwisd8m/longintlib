#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include <stdbool.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_scan_dec(lil_t *src) {
    // scan decimal representation of source
    
    int sign = LIL_PLUS;
    bool sign_check = true; // true when "sign input" check is required
    bool leading_zero_check = true; // true when "leading zero(es) check" is required
    
    const uint64_t lim = LIL_BASE * src->size;
    char ch = 0;
    
    // default input
    LIL_SET_NULL(src);
    
    while (lil_len(src) < lim) {
        ch = getchar();
        
        // check termination symbols
        if ((ch == '\n') or (ch == '\0') or (ch == EOF) or feof(stdin)) break;
        
        // condition to stop "leading zero(es) input" check
        if ((ch != '0') and leading_zero_check and (not sign_check)) {
            leading_zero_check = false; // stop "leading zero(es) input" check
        }
        
        // first symbol input
        if (sign_check) {
            if (ch == '-') {
                sign = LIL_MINUS;
                leading_zero_check = true; // continue "leading zero(es) input" check
            }
            else {
                if (ch == '0') leading_zero_check = true; // continue "leading zero(es) input" check
                else leading_zero_check = false; // stop "leading zero(es) input" check
            }
            sign_check = false; // stop "sign input" check
        }
        
        // digit input 
        if ((not sign_check) and (not leading_zero_check)) {
            if ((ch < '0') or (ch > '9')) {
                errno = ERR_INVALID_INPUT;
                perror("An invalid character entered");
                exit(EXIT_FAILURE);
            }
            lil_short_mul(src, 10); // NOTE: operation sets positive sign
            lil_short_add(src, (uint64_t)(ch - '0'));
        }
    }
    
    // correct result sign
    src->sign = (lil_is_null(src)) ? LIL_PLUS : sign;
    return 0;
}
