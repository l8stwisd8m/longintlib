#include <stddef.h>
#include "longintlib.h"

int lil_is_one(lil_t *src) {
    // return 1 if source is one, 0 otherwise
    
    for(size_t i = 1; i < src->size; i++) {
        if (src->val[i]) return 0;
    }
    
    return (src->val[0] == 1);
}
