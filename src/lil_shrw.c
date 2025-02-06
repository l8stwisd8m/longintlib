#include "../include/longintlib.h"

void lil_shrw(lil_t *src) {
    // right shift by word size
    for (int i = 0; i < src->size - 1; i++) {
        src->val[i] = src->val[i + 1];
    }
    src->val[src->size - 1] = 0;
}
