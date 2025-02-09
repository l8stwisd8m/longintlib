#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#define LIL_PH_MASK 0xf000000000000000
#define PREFIX
#define SEPARATOR
#define NEW_LINE
#if 0
#define PRINT_SIGN
#endif /* if 0 */

void lil_print_hex(lil_t *src) {
    // print hexadecimal representation of source
     
    #ifdef PRINT_SIGN
    if (src->sign == LIL_MINUS) putchar('-');
    #endif /* ifdef PRINT_SIGN */
    
    #ifdef PREFIX
    printf("0x");
    #endif /* ifdef PREFIX */
    
    #ifdef SEPARATOR
    putchar(' ');
    #endif /* ifdef SEPARATOR */

    for (int i = src->size - 1; i >= 0; i--) {
        for (int j = 0; j < LIL_BASE; j += 4) {
            if (LIL_PH_MASK & (src->val[i] << j)) {
                printf("%"PRIx64"", src->val[i]);
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
}
