#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <iso646.h>
#include <string.h>
#include <stdbool.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_str_dec(lil_t *src, char *str) {
    // extract representation of source from decimal string
    
    int sign = LIL_PLUS;
    bool sign_check = true; // true when "sign input" check is required
    bool leading_zero_check = true; // true when "leading zero(es) check" is required
    
    // default input
    src->sign = LIL_PLUS;
    LIL_SET_NULL(src);

    char ch = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        ch = str[i];
        
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
