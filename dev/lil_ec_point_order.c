#include "../include/longintlib.h"
#include "../include/longintmacro.h"
#include "../include/longintcurve.h"

int lil_ec_point_order(lil_ec_t *curve, lil_t *dst, lil_point_t *src) {
    // order of source point
    
    // TODO: check exceptions
    
    // default result
    LIL_SET_NULL(dst);
    
    if (LIL_EC_SPECIAL_POINT(src)) {
        return 0;
    }
    
    lil_point_t *tmp, *res;
    LIL_EC_CALLOC(tmp, curve->m->size);
    LIL_EC_CALLOC(res, curve->m->size);
    lil_ec_cpy(res, src);
    
    do {
        lil_ec_cpy(tmp, res);
        lil_ec_add(curve, res, tmp, src);
        lil_inc(dst);
    } while (not LIL_EC_SPECIAL_POINT(res));
    
    LIL_EC_FREE(tmp);
    LIL_EC_FREE(res);
    return 0;
}
