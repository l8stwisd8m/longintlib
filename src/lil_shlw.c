#include "../include/longintlib.h"

void lil_shlw(lil_t *src) {
    // left shift by word size
    for (int i = src->size - 1; i > 0; i--) {
        src->val[i] = src->val[i - 1];
    }
    src->val[0] = 0;
}
