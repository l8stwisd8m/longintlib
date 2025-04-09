#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_prng(lil_t *src, size_t seed) {
    // set source value to a random number
    
    srand(seed);
    for (size_t i = 0; i < src->size; i++) {
        src->val[i] = (uint64_t)rand();
        src->val[i] = (src->val[i] << LIL_SPLIT) | (uint64_t)rand();
    }
    
    return 0;
}
