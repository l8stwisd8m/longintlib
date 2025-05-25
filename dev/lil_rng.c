#include <stddef.h>
#include <stdint.h>
#include <immintrin.h>
#include "longintlib.h"
#define ATTEMPTS 10
#define RNG_SUCCESS 0
#define RNG_FAIL 1

int lil_rng(lil_t *src) {
    // set source value to a random number
    
    int flag = 1;
    int retries = 0;
    unsigned long long tmp = 0; // it is uint64_t actually
    
    for (size_t i = 0; i < src->size; i++) {
        flag = RNG_FAIL;
        retries = ATTEMPTS;
        while (retries--) {
            if (_rdrand64_step(&tmp)) {
                src->val[i] = tmp;  
                flag = RNG_SUCCESS;
                break;
            }
        }
        if (flag) return RNG_FAIL;
    }
    
    return RNG_SUCCESS;
}
