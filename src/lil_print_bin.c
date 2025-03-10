#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#define PREFIX
#define SEPARATOR
#define NEW_LINE
#define PRINT_SIGN

int lil_print_bin(lil_t *src) {
    // print binary representation of source
    
    #ifdef PRINT_SIGN
    if ((src->sign == LIL_MINUS) and (not lil_is_null(src))) putchar('-');
    #endif /* ifdef PRINT_SIGN */
    
    #ifdef PREFIX
    printf("0b");
    #endif /* ifdef PREFIX */
    
    #ifdef SEPARATOR
    putchar(' ');
    #endif /* ifdef SEPARATOR */
    
    for (size_t i = 0; i < src->size; i++) {
        for (int j = 0; j < LIL_BASE; j++) {
            if (LIL_MSBIT & (src->val[src->size - i - 1] << j)) putchar('1');
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
