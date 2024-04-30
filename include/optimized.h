#ifndef RECURSIVE_INT_OPTIMIZED
#define RECURSIVE_INT_OPTIMIZED

#include "./base.h"

recursive_int *recursive_int_optimize(recursive_int *);

recursive_int *recursive_int_diff(recursive_int *, recursive_int *);
recursive_int *recursive_int_sum(recursive_int *, recursive_int *);

recursive_int *de_zero(recursive_int *);

bool lesseroe(long long x, long long y); 
bool greateroe(long long x, long long y); 
recursive_int *recursive_int_minimize(recursive_int *);

bool recursive_int_equal_optimized(recursive_int *, recursive_int *);
bool optimized_is_zero(recursive_int *);
recursive_int *recursive_int_optimized_revert(recursive_int *);

#endif