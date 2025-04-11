#!/bin/bash

shopt -s nullglob

# prerequisites
mv dev/lil_prng.c src/ 2>/dev/null || true
mv dev/lil_jacobi.c src/ 2>/dev/null || true
mv dev/lil_sqrt_mod.c src/ 2>/dev/null || true

# headers
mv dev/longintcurve.h include/ 2>/dev/null || true

# source files
mv dev/lil_ec_*.c src/ 2>/dev/null || true

# test files
mv dev/test_lil_ec_*.c test/ 2>/dev/null || true

make
