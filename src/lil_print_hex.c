#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include <inttypes.h>
#include "longintlib.h"
#include "longintconst.h"
#define LIL_PH_MASK 0xf000000000000000

int lil_print_hex(lil_t *src) {
    // print hexadecimal representation of source
    
    #ifdef LIL_PRINT_SIGN
    if ((src->sign == LIL_MINUS) and (not lil_is_null(src))) putchar('-');
    #endif /* ifdef LIL_PRINT_SIGN */
    
    #ifdef LIL_PRINT_PREFIX
    printf("0x");
    #endif /* ifdef LIL_PRINT_PREFIX */
    
    #ifdef LIL_PRINT_SEPARATOR
    putchar(' ');
    #endif /* ifdef LIL_PRINT_SEPARATOR */

    for (size_t i = 0; i < src->size; i++) {
        for (int j = 0; j < LIL_BASE; j += 4) {
            if (LIL_PH_MASK & (src->val[src->size - i - 1] << j)) {
                printf("%"PRIx64"", src->val[src->size - i - 1]);
                break;
            }
            else putchar('0');
        }
        #ifdef LIL_PRINT_SEPARATOR
        putchar(' ');
        #endif /* ifdef LIL_PRINT_SEPARATOR */
    }
    
    #ifdef LIL_PRINT_NEW_LINE
    putchar('\n');
    #endif /* ifdef LIL_PRINT_NEW_LINE */
    
    return 0;
}
