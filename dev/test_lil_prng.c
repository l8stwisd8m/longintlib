#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"

Test(test_lil_prng, zero_seed) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_prng(&a, 0);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0x6b8b4567327b23c6, 0x643c986966334873, 0x74b0dc5119495cff, 0x2ae8944a625558ec};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}

Test(test_lil_prng, nonzero_seed) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_prng(&a, 88);
    cr_expect_eq(flag, LIL_NO_ERROR);
    uint64_t expected_arr[LIL_256_BIT] = {0x024daf712a402507, 0x0df2ecc512b50bca, 0x55c7862d33b4e782, 0x5ef0aa1f7773edc1};
    cr_expect_arr_eq(a.val, expected_arr, a.size);
}
