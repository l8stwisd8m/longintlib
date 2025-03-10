#include <stddef.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_dec(lil_t *src) {
    // decrement source value
    
    for (size_t i = 0; i < src->size; i++) {
        if (src->val[i] == 0) src->val[i] -= 1;
        else {
            src->val[i] -= 1;
            return 0;
        }
    }
    return LIL_OVERFLOW;
}
