#include <stdint.h>
#include <criterion/criterion.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintprime.h"

Test(test_lil_primality, empty_value) {
    uint64_t arr_a[LIL_256_BIT] = {0};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_TEST_FAIL);
}

Test(test_lil_primality, input_is_one) {
    uint64_t arr_a[LIL_256_BIT] = {1};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_TEST_FAIL);
}

Test(test_lil_primality, input_is_two) {
    uint64_t arr_a[LIL_256_BIT] = {2};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_PRIME);
}

Test(test_lil_primality, input_is_small_prime) {
    uint64_t arr_a[LIL_256_BIT] = {5};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_PRIME);
}

Test(test_lil_primality, input_is_small_even) {
    uint64_t arr_a[LIL_256_BIT] = {4};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_COMPOSITE);
}

Test(test_lil_primality, input_is_short_composite) {
    uint64_t arr_a[LIL_256_BIT] = {1234567};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_COMPOSITE);
}

Test(test_lil_primality, input_is_short_prime) {
    uint64_t arr_a[LIL_256_BIT] = {1307};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_PRIME);
}

Test(test_lil_primality, input_is_long_composite) {
    uint64_t arr_a[LIL_256_BIT] = {0xf6b6e3d5e6e0cad1, 0x691b3453da7cdc79, 0x00000001aa6d4269};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_COMPOSITE);
}

Test(test_lil_primality, input_is_long_prime) {
    uint64_t arr_a[LIL_256_BIT] = {0x8eee6d4f2d80b0d1, 0x51dab914b9451b6b, 0x8f1fdf0aadb6ccfb, 0x01fbdbab8222514f};
    long_int a = {PLUS, arr_a, LIL_256_BIT};
    int flag = lil_primality(&a);
    cr_expect_eq(flag, LIL_PRIME);
}
