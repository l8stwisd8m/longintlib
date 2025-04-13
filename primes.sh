#!/bin/bash

shopt -s nullglob

# prerequisites
mv dev/lil_prng.c src/ 2>/dev/null || true
mv dev/lil_jacobi.c src/ 2>/dev/null || true

# headers
mv dev/longintprime.h include/ 2>/dev/null || true

# source files
mv dev/lil_primality.c src/ 2>/dev/null || true
mv dev/lil_miller_rabin.c src/ 2>/dev/null || true
mv dev/lil_solovay_strassen.c src/ 2>/dev/null || true

# test files
mv dev/test_lil_primality.c test/ 2>/dev/null || true
mv dev/test_lil_miller_rabin.c test/ 2>/dev/null || true
mv dev/test_lil_solovay_strassen.c test/ 2>/dev/null || true

make
