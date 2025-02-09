#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#define PREFIX
#define SEPARATOR
#define NEW_LINE
#if 0
#define PRINT_SIGN
#endif /* if 0 */

void lil_print_bin(lil_t *src) {
    // print binary representation of source
    
    #ifdef PRINT_SIGN
    if (src->sign == LIL_MINUS) putchar('-');
    #endif /* ifdef PRINT_SIGN */
    
    #ifdef PREFIX
    printf("0b");
    #endif /* ifdef PREFIX */
    
    #ifdef SEPARATOR
    putchar(' ');
    #endif /* ifdef SEPARATOR */
    
    for (int i = src->size - 1; i >= 0; i--) {
        for (int j = 0; j < LIL_BASE; j++) {
            if (LIL_MSBIT & (src->val[i] << j)) putchar('1');
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
