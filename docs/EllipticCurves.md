# Elliptic Curves over Finite Fields

## Overview

The `longintcurve.h` contains two basic types, prototypes of functions and various macros for operating points on elliptic curves of normal form over finite fields. 
Weierstrass' curve is an equation of the form:

$$y^2 = x^3+ax+b$$

where the inequality of the elliptic discriminant $\Delta=-16(4a^3+27b^2)$ to zero is a condition for the curve to be non-singular.

**Prerequisites**:  
• `lil_prng.c`  
• `lil_jacobi.c`  
• `lil_sqrt_mod.c`  

The `elliptic_curves.sh` script can be used to move all the necessary files, required by this module, to `src`, `include` and `test` directories, and recompile the library automatically. One can just run:
```
chmod +x elliptic_curves.sh
./elliptic_curves.sh
```

## Elliptic Curve type
The `lil_ec_t` structure definition represents coefficients of of the equation of an elliptic curve and the modulus, which **should** be prime number. Choise of a composite modulus can be useful for some applications — for instance, in factorization algotithms.  
```
typedef struct {
    lil_t *a;
    lil_t *b;
    lil_t *m;
} lil_ec_t;
```
All three parameters: `a`, `b` and `m` should be long integers, with a requirement for modulus `m` to be positive non-zero [prime] number.

## Elliptic Curve Point type
The `lil_ec_t` structure definition represents a point $(x, y)$ on the curve.
```
typedef struct {
    lil_t *x;
    lil_t *y;
} lil_point_t;
```
Elements `x` and `y` **can** be greater than modulus or negative. However, during any calculations both will be updated so they belong to the range $[0, m)$. Unlike the main library functions, ones used here do not guarantee that input parameters of functions will not be changed during operations.

## Functions & Macros
Description will be updated as soon as possible >.<