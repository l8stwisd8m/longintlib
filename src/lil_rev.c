#include <stddef.h>
#include <stdint.h>
#include "longintlib.h"

int lil_rev(lil_t *src) {
    // reverse source values order
    
    uint64_t tmp;
    
    for (size_t i = 0; i < src->size / 2; i++) {
        tmp = src->val[src->size - 1 - i];
        src->val[src->size - 1 - i] = src->val[i];
        src->val[i] = tmp;
    }
    
    return 0;
}
