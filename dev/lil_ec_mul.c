#include "longintlib.h"
#include "longintcurve.h"

int lil_ec_mul(lil_ec_t *curve, lil_point_t *dst, lil_point_t *src_p, lil_t *src_n) {
    // point p multiplied by long int n
    
    // TODO: check exceptions
    
    // TODO: correct input
    
    // p = 0 or n = 0 => p * n = 0
    if (LIL_EC_SPECIAL_POINT(src_p) or lil_is_null(src_n)) {
        LIL_EC_SET_NULL(dst);
        return 0;
    }
    
    lil_point_t *tmp;
    LIL_EC_MALLOC(tmp, curve->m->size);
    lil_ec_cpy(dst, src_p);
    
    uint64_t shift = lil_len(src_n) - 1;
    int64_t bit_shift = 0;
    // iterate bits of source n one by one, from the MSB (not including MSB) to the LSB
    for (int64_t i = (int64_t)(shift / LIL_BASE); i >= 0; i--) {
        bit_shift = (i == (int64_t)(shift / LIL_BASE)) ? (int64_t)(shift % LIL_BASE) - 1 : LIL_BASE - 1;
        for (int64_t j = bit_shift; j >= 0; j--) {
            lil_ec_cpy(tmp, dst);
            lil_ec_add(curve, dst, tmp, tmp);
            if ((src_n->val[i] >> j) & 1) {
                lil_ec_cpy(tmp, dst);
                lil_ec_add(curve, dst, tmp, src_p);
            }
        }
    }
    
    LIL_EC_FREE(tmp);
    return 0;
}
