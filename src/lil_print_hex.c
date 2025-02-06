#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#define LIL_PH_MASK 0xf000000000000000

void lil_print_hex(lil_t *src) {
    // print hexadecimal representation of source
    printf("0x ");
    for (int i = src->size - 1; i >= 0; i--) {
        for (int j = 0; j < LIL_BASE; j += 4) {
            if (LIL_PH_MASK & (src->val[i] << j)) {
                printf("%"PRIx64"", src->val[i]);
                break;
            }
            else putchar('0');
        }
        putchar(' ');
    }
    putchar('\n');
}
