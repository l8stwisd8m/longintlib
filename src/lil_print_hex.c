#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#define LIL_PH_MASK 0xf000000000000000
#define PREFIX
#define SEPARATOR
#define NEW_LINE
#define PRINT_SIGN

int lil_print_hex(lil_t *src) {
    // print hexadecimal representation of source
     
    #ifdef PRINT_SIGN
    if ((src->sign == LIL_MINUS) and (not lil_is_null(src))) putchar('-');
    #endif /* ifdef PRINT_SIGN */
    
    #ifdef PREFIX
    printf("0x");
    #endif /* ifdef PREFIX */
    
    #ifdef SEPARATOR
    putchar(' ');
    #endif /* ifdef SEPARATOR */

    for (size_t i = 0; i < src->size; i++) {
        for (int j = 0; j < LIL_BASE; j += 4) {
            if (LIL_PH_MASK & (src->val[src->size - i - 1] << j)) {
                printf("%"PRIx64"", src->val[src->size - i - 1]);
                break;
            }
            else putchar('0');
        }
        #ifdef SEPARATOR
        putchar(' ');
        #endif /* ifdef SEPARATOR */
    }
     
    #ifdef NEW_LINE
    putchar('\n');
    #endif /* ifdef NEW_LINE */
    
    return 0;
}
