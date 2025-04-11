#include "../include/longintlib.h"
#include "../include/longintcurve.h"

int lil_ec_short_mul(lil_ec_t *curve, lil_point_t *dst, lil_point_t *src_p, uint64_t src_n) {
    // point p multiplied by short int n
    
    // TODO: check exceptions
    
    // TODO: correct input
    
    // p = 0 or n = 0 => p * n = 0
    if (LIL_EC_SPECIAL_POINT(src_p) or (src_n == 0)) {
        LIL_EC_SET_NULL(dst);
        return 0;
    }
    
    lil_point_t *tmp;
    LIL_EC_CALLOC(tmp, curve->m->size);
    lil_ec_cpy(dst, src_p);
    
    size_t ctr = LIL_BASE - (1 +__builtin_clzll(src_n));
    while(ctr--) {
        lil_ec_cpy(tmp, dst);
        lil_ec_add(curve, dst, tmp, tmp);
        if ((src_n >> ctr) & 1) {
            lil_ec_cpy(tmp, dst);
            lil_ec_add(curve, dst, tmp, src_p);
        }
    }
    
    LIL_EC_FREE(tmp);

    return 0;
}
