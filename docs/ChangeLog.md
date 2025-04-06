# Change log

## Release v.0.1
Initial release, which includes headers and dynamic library file. Source files contain documentation, some examples, a template, test files, makefile, script for gathering coverage information, basic and additional functions.

There are three headers:
1. `longintlib.h` containing prototypes of functions, described below;
2. `longintconst.h`for often used constants (sign, utility, size constants, bitmasks and errors enumeration);
3. `longintmacro.h` for useful function-like macros (check if value is even / odd, least / most significant digit, copy value, set null, memory allocation, clean memory allocation, memory freeing, bitwise or / and / not / xor operations).
  
Dynamic library file, `longintlib.so`provides the following features:
1. Basic functions (reverse value, copy value, get value length, compare values, compare lengths of values, compare absolute values, check if value is null / is even / is odd);
2. Print & scan functions (print and scan value in binary, decimal and hexadecimal format);
3. Basic math functions (addition, subtraction, arithmetic sum, multiplication, division, modulus and greatest common divisor);
4. Unary math functions (increment and decrement);
5. Shifts (left and right shifts by one bit / by word size / by n bits);
6. Short operations (addition, subtraction, multiplication, division, modulus, and exponentiation by modulo);
7. Modular arithmetic (update value by modulus, modulo inversion / sum / multiplication / division, and exponentiation by modulo).

Overall coverage rate:
  source files: 42
  lines.......: 93.6% (1032 of 1102 lines)
  functions...: 100.0% (46 of 46 functions)
  branches....: 80.7% (787 of 975 branches)