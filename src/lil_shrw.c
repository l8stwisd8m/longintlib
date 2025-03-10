#include <stddef.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_shrw(lil_t *src) {
    // right shift by word size
    
    int flag = (src->val[0]) ? LIL_OVERFLOW : 0;
    
    for (size_t i = 0; i < src->size - 1; i++) {
        src->val[i] = src->val[i + 1];
    }
    src->val[src->size - 1] = 0;
    
    return flag;
}
