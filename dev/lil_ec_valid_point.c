#include "longintlib.h"
#include "longintmacro.h"
#include "longintcurve.h"

int lil_ec_valid_point(lil_ec_t *curve, lil_point_t *src) {
    // check if source point belongs to curve
    
    // TODO: check exceptions
    
    // check is both point coordinates are equal to zero
    if (LIL_EC_SPECIAL_POINT(src)) return LIL_EC_SPECIAL;
    
    int flag = 0;
    long_int *val_y, *val_x;
    LIL_MALLOC(val_y, curve->m->size);
    LIL_MALLOC(val_x, curve->m->size);
    
    // evaluation of coordinates for comparison
    lil_mul_mod(val_y, src->y, src->y, curve->m); // y ^ 2 mod m
    lil_ec_evaluate(curve, val_x, src->x);        // x ^ 3 + a * x + b mod m
    flag = lil_cmp(val_y, val_x);                 // comparison
    
    LIL_FREE(val_y);
    LIL_FREE(val_x);
    
    if (flag) return LIL_EC_INVALID;
    else return LIL_EC_VALID;
}
