#include <assert.h>
#include "longintlib.h"
#include "longintmacro.h"
#include "longintcurve.h"

int lil_ec_prng_point(lil_ec_t *curve, lil_point_t *dst, size_t seed) {
    // long integer source embedding into point
    
    // TODO: check exceptions
    
    long_int *eval;
    LIL_MALLOC(eval, curve->m->size);
    
    do {
        lil_prng(dst->x, seed++);
        lil_val_mod(dst->x, curve->m);
        lil_ec_evaluate(curve, eval, dst->x);
    } while (lil_jacobi(eval, curve->m) != 1);
    lil_sqrt_mod(dst->y, eval, curve->m);
    
    //assert(lil_ec_valid_point(curve, dst) == LIL_EC_VALID);
    
    LIL_FREE(eval);
    return 0;
}
