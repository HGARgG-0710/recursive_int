#ifndef RECURSIVE_INT
#define RECURSIVE_INT

#include "optimized.h"

recursive_int *recursive_int_add(recursive_int *, recursive_int *);
recursive_int *recursive_int_add_i(recursive_int *, long long);

recursive_int *recursive_int_mult(recursive_int *, recursive_int *);

bool recursive_int_greater(recursive_int *, recursive_int *);
bool recursive_int_equal(recursive_int *, recursive_int *);

bool recursive_int_sign(recursive_int *);
recursive_int *recursive_int_depth(recursive_int *);

#endif