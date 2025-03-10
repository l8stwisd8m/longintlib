#include <stddef.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_shl(lil_t *src) {
    // bitwise left shift
    
    uint64_t tmp = 0;
    uint64_t carry_value = 0;
    
    for (size_t i = 0; i < src->size; i++) {
        tmp = (LIL_MSBIT & src->val[i]) >> (LIL_BASE - 1);
        src->val[i] = (src->val[i] << 1) ^ carry_value;
        carry_value = tmp;
    }
    
    if (carry_value) return LIL_OVERFLOW;
    else return 0;
}
