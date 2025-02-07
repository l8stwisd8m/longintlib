#include <stdio.h>
#include "../../include/longintlib.h"
#include "test_utils.h"

void print_args (lil_t *a, lil_t *b) {
    printf("a:\t");
    lil_print_hex(a);
    printf("b:\t");
    lil_print_hex(b);
}
