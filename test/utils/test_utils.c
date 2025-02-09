#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "../../include/longintlib.h"
#include "test_utils.h"

void print_args(lil_t *a, lil_t *b) {
    printf("a:\t");
    lil_print_hex(a);
    printf("b:\t");
    lil_print_hex(b);
}

void short_print_args(lil_t *a, uint64_t b) {
    printf("a:\t");
    lil_print_hex(a);
    printf("b:\t0x %"PRIx64"\n", b);
}
