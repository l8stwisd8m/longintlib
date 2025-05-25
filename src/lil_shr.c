#include <stddef.h>
#include <stdint.h>
#include "longintlib.h"
#include "longintconst.h"

int lil_shr(lil_t *src) {
    // bitwise right shift
    
    uint64_t tmp = 0;
    uint64_t carry_value = 0;
    
    for (size_t i = 0; i < src->size; i++) {
        tmp = (LIL_LSBIT & src->val[src->size - i - 1]) << (LIL_BASE - 1);
        src->val[src->size - i - 1] = (src->val[src->size - i - 1] >> 1) ^ carry_value;
        carry_value = tmp;
    }
    
    if (carry_value) return LIL_OVERFLOW;
    else return 0;
}
