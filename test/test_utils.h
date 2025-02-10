#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

#include <stdio.h>
#include <inttypes.h>
#include "../include/longintlib.h"

#define BASE_MAX 0xffffffffffffffff
#define N 4

#define PRINT_ARG(ARG) \
    printf("%s:\t", #ARG); \
    lil_print_hex(ARG);

#define PRINT_SHORT_ARG(ARG) \
    printf("%s:\t0x %"PRIx64"\n", #ARG, ARG);

#endif // !_TEST_UTILS_H_
