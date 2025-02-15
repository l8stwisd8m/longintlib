#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#define VAL_SIZE 20
#define PRIME_AMNT 15

// set source value null
#define LIL_STATIC_SET_NULL(SRC) \
    for (int i = 0; i < SRC.size; SRC.val[i++] = 0);

int main(int argc, char *argv[]) {
    // Fermat & Mersenne primes
    
    uint64_t fermat_exp = 0;
    uint64_t fermat_prime = 0;
    printf("Fermat primes: \n");
    for (int i = 0; i < 5; i++) {
        fermat_exp = 1 << i;
        fermat_prime = (1 << fermat_exp) + 1;
        printf("%"PRId64"\n", fermat_prime);
    }
    
    uint64_t mersenne_val[VAL_SIZE] = {0};
    uint64_t mersenne_exp[15] = {2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607, 1279};
    long_int mersenne_prime = {PLUS, mersenne_val, VAL_SIZE};
    printf("Mersenne primes: \n");
    for (int i = 0; i < PRIME_AMNT; i++) {
        mersenne_prime.val[0] = 1;
        lil_shln(&mersenne_prime, mersenne_exp[i]);
        lil_dec(&mersenne_prime);
        lil_print_dec(&mersenne_prime);
        LIL_STATIC_SET_NULL(mersenne_prime);
    }
    
    return 0;
}
