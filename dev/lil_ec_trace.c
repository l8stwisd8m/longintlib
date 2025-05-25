#include "longintlib.h"
#include "longintmacro.h"
#include "longintcurve.h"

int lil_ec_curve_trace(lil_ec_t *curve, lil_t *dst) {
    // frobenius trace of a curve
    
    // TODO: check exceptions
    
    long_int *order;
    LIL_MALLOC(order, curve->m->size);
    
    // trace = m + 1 - order (it CAN be negative)
    lil_ec_curve_order(curve, order);
    lil_dec(order);
    LIL_SET_MINUS(order);
    LIL_SET_PLUS(curve->m); // just in case
    lil_sum(dst, order, curve->m);
    
    LIL_FREE(order);
    return 0;
}
