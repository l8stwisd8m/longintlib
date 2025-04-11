#include "../include/longintlib.h"
#include "../include/longintmacro.h"
#include "../include/longintcurve.h"

int lil_ec_sub(lil_ec_t *curve, lil_point_t *dst, lil_point_t *src_p, lil_point_t *src_q) {
    // subtraction q from p
    
    // TODO: check exceptions
    
    // q = 0 => p - q = p
    if (LIL_EC_SPECIAL_POINT(src_q)) {
        lil_ec_cpy(dst, src_p);
        return 0;
    }

    long_int *tmp_y;
    LIL_MALLOC(tmp_y, src_q->y->size);
    LIL_CPY_VAL(tmp_y, src_q->y);
    LIL_SET_MINUS(tmp_y);
    lil_val_mod(tmp_y, curve->m);
    
    lil_point_t *tmp_q;
    tmp_q = (lil_point_t *)malloc(sizeof(lil_point_t));
    tmp_q->x = src_q->x;
    tmp_q->y = tmp_y;
    
    lil_ec_add(curve, dst, src_p, tmp_q); // p - q
    
    LIL_FREE(tmp_y);
    free(tmp_q);
    return 0;
}
