// ! order definitions...;

#ifndef RECURSIVE_INT
#define RECURSIVE_INT

#include <stdbool.h>

typedef struct
{
	recursive_int *ri;
	long long value;
} recursive_int;

recursive_int *recursive_int_copy(recursive_int *);

recursive_int *recursive_int_optimize(recursive_int *);

void recursive_int_addinv(recursive_int *);

recursive_int *recursive_int_inc(recursive_int *);
recursive_int *recursive_int_dec(recursive_int *);

recursive_int *recursive_int_add(recursive_int *, recursive_int *);
recursive_int *recursive_int_add_i(recursive_int *, long long);

recursive_int *recursive_int_diff(recursive_int *, recursive_int *);
// ! undone(1)
recursive_int *recursive_int_sum(recursive_int *, recursive_int *);

recursive_int *recursive_int_mult(recursive_int *, recursive_int *);

recursive_int *alloc_recursive_int(long long, recursive_int *);
recursive_int *free_recursive_int(recursive_int *);

recursive_int *get_negative(recursive_int *);
recursive_int *get_positive(recursive_int *);

// ! undone yet (1)
bool recursive_int_greater(recursive_int *, recursive_int *);
bool recursive_int_equal(recursive_int *, recursive_int *);
bool recursive_int_equal_optimized(recursive_int *, recursive_int *);

void recursive_int_abs(recursive_int *);

bool recursive_int_sign(recursive_int *);
bool recursive_int_llfit(recursive_int *);

recursive_int *recursive_int_minize(recursive_int *);
// ! undone (2)
recursive_int *recursive_int_minize_positive(recursive_int *);
recursive_int *recursive_int_minize_negative(recursive_int *);

recursive_int * recursive_zero(); 

#endif