#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

void lil_mul_mod(lil_t *dst, lil_t *src_a, lil_t *src_b, lil_t *src_m) {
    // multiplication of a and b modulo m
    
    assert(lil_is_null(src_m) == 0);
    assert(lil_cmp_val(src_a, src_m) == -1); // a < m
    assert(lil_cmp_val(src_b, src_m) == -1); // b < m
    assert((dst->size == src_a->size) and (src_a->size == src_b->size) and (src_b->size == src_m->size));
    
    // default: result
    dst->sign = LIL_PLUS;
    LIL_SET_NULL(dst);
    
    if (lil_is_null(src_a) or lil_is_null(src_b)) {
        return; // a = 0 or b = 0 => a * b = 0
    }
    
    uint64_t shift = 0;
    int bit_shift = 0;
    if (lil_cmp_len(src_a, src_b) == 1) {
        shift = lil_len(src_b) - 1;
        // iterate source b bits one by one, from the MSB to the LSB
        for (int i = (int)(shift / LIL_BASE); i >= 0; i--) {
            bit_shift = (i == (int)(shift / LIL_BASE)) ? (int)(shift % LIL_BASE) : LIL_BASE - 1;
            for (int j = bit_shift; j >= 0; j--) {
                lil_shl(dst); 
                if (lil_cmp_val(dst, src_m) == 1) {
                    lil_sub(dst, src_m); // dst -= m
                }
                if ((src_b->val[i] >> j) & LIL_LSBIT) {
                    lil_add(dst, src_a); // dst += b
                }
                if (lil_cmp_val(dst, src_m) == 1) {
                    lil_sub(dst, src_m); // dst -= m
                }
            }
        }
    }
    else {
        shift = lil_len(src_a) - 1;
        // iterate source a bits one by one, from the MSB to the LSB
        for (int i = (int)(shift / LIL_BASE); i >= 0; i--) {
            bit_shift = (i == (int)(shift / LIL_BASE)) ? (int)(shift % LIL_BASE) : LIL_BASE - 1;
            for (int j = bit_shift; j >= 0; j--) {
                lil_shl(dst); 
                if (lil_cmp_val(dst, src_m) == 1) {
                    lil_sub(dst, src_m); // dst -= m
                }
                if ((src_a->val[i] >> j) & LIL_LSBIT) {
                    lil_add(dst, src_b); // dst += b
                }
                if (lil_cmp_val(dst, src_m) == 1) {
                    lil_sub(dst, src_m); // dst -= m
                }
            }
        }
    }
}
