#include <stdio.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void lil_print_bin(lil_t *src) {
    // print binary representation of source
    printf("0b ");
    for (int i = src->size - 1; i >= 0; i--) {
        for (int j = 0; j < LIL_BASE; j++) {
            if (LIL_MSBIT & (src->val[i] << j)) putchar('1');
            else putchar('0');
        }
        putchar(' ');
    }
    putchar('\n');
}
