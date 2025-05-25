#include <stddef.h>
#include "longintlib.h"
#include "longintconst.h"

int lil_inc(lil_t *src) {
    // increment source value
    
    for (size_t i = 0; i < src->size; i++) {
        if (src->val[i] + 1 < src->val[i]) src->val[i] += 1;
        else {
            src->val[i] += 1;
            return 0;
        }
    }
    return LIL_OVERFLOW;
}
