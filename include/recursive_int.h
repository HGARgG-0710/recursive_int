#ifndef RECURSIVE_INT
#define RECURSIVE_INT

#include "optimized.h"

recursive_int *recursive_int_add(recursive_int *, recursive_int *);
recursive_int *recursive_int_add_i(recursive_int *, long long);

recursive_int *recursive_int_mult(recursive_int *, recursive_int *);

bool recursive_int_greater(recursive_int *, recursive_int *);
bool recursive_int_equal(recursive_int *, recursive_int *);

bool recursive_int_sign(recursive_int *);

bool is_zero(recursive_int * ri); 
bool recursive_int_llfit(recursive_int *);

#endif