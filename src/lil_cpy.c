#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_cpy(lil_t *dst, lil_t *src) {
    // copy source structure to destination
    
    #ifdef LIL_OPERAND_SIZES
    if (dst->size < src->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid size of destination value; source value can not be copied");
        exit(EXIT_FAILURE); // invalid operand sizes
    }
    #endif /* LIL_OPERAND_SIZES_CHECK */
    
    dst->sign = src->sign;
    for (size_t i = 0; i < src->size; i++) {
        dst->val[i] = src->val[i];
    }
    
    if (src->size < dst->size) {
        dst->size = src->size;
        return LIL_TRUNCATED;
    }
    else {
        dst->size = src->size;
        return 0;
    }
}
