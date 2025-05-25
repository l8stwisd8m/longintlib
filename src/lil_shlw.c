#include <stddef.h>
#include "longintlib.h"
#include "longintconst.h"

int lil_shlw(lil_t *src) {
    // left shift by word size
    
    int flag = (src->val[src->size - 1]) ? LIL_OVERFLOW : 0;
    
    for (size_t i = src->size - 1; i > 0; i--) {
        src->val[i] = src->val[i - 1];
    }
    src->val[0] = 0;
    
    return flag;
}
