#include "../include/longintlib.h"
#include "../include/longintcurve.h"

int lil_ec_cpy(lil_point_t *dst, lil_point_t *src) {
    // copy source point to destination
    
    // TODO: exceptions
    
    lil_cpy(dst->x, src->x);
    lil_cpy(dst->y, src->y);
    return 0;
}
