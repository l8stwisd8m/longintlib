#include <stddef.h>
#include "../include/longintlib.h"

int lil_is_null(lil_t *src) {
    // return 1 if source is empty, 0 otherwise
    
    for (size_t i = 0; i < src->size; i++) {
        if (src->val[i]) return 0;
    }
    
    return 1;
}
