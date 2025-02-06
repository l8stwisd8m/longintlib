#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void lil_shr(lil_t *src) {
    // bitwise right shift
    uint64_t tmp = 0;
    uint64_t carry_value = 0;
    for (int i = src->size - 1; i >= 0; i--) {
        tmp = (LIL_LSBIT & src->val[i]) << (LIL_BASE - 1);
        src->val[i] = (src->val[i] >> 1) ^ carry_value;
        carry_value = tmp;
    }
}
