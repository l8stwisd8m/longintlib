#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintcurve.h"

int lil_ec_cmp(lil_ec_t *curve, lil_point_t *src_p, lil_point_t *src_q) {
    // return 1 if point p is equal to q, 0 otherwise
    
    // TODO: exceptions
    
    // correct input
    lil_val_mod(src_p->x, curve->m);
    lil_val_mod(src_p->y, curve->m);
    lil_val_mod(src_q->x, curve->m);
    lil_val_mod(src_q->y, curve->m);
    
    for(size_t i = 0; i < curve->m->size; i++) {
        if ((src_p->x->val[i] != src_q->x->val[i]) or \
            (src_p->y->val[i] != src_q->y->val[i])) return 0;
    }
    
    return 1;
}
