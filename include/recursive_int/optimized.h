#ifndef RECURSIVE_INT_OPTIMIZED
#define RECURSIVE_INT_OPTIMIZED

#include "./base.h"

recursive_int *recursive_int_optimize(recursive_int *);

recursive_int *recursive_int_diff(recursive_int *);
// ! undone (is supposed to be preserving the 'optimized'-ness); 
recursive_int *recursive_int_sum(recursive_int *);

recursive_int *recursive_int_minize(recursive_int *);
// ! undone (2)
recursive_int *recursive_int_minize_positive(recursive_int *);
recursive_int *recursive_int_minize_negative(recursive_int *);

bool recursive_int_equal_optimized(recursive_int *, recursive_int *);

#endif