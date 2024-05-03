#ifndef RECURSIVE_INT_BASE
#define RECURSIVE_INT_BASE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct _rint
{
	struct _rint *ri;
	long long value;
} recursive_int;

recursive_int *alloc_recursive_int(long long v, recursive_int *);
recursive_int *free_recursive_int(recursive_int *);
recursive_int *recursive_int_copy(recursive_int *);

recursive_int *recursive_int_abs(recursive_int *);
recursive_int *recursive_int_addinv(recursive_int *);

recursive_int *recursive_int_inc(recursive_int *);
recursive_int *recursive_int_dec(recursive_int *);

recursive_int *recursive_zero();
recursive_int *recursive_int_from_ll(long long value);

recursive_int *get_negative(recursive_int *);
recursive_int *get_positive(recursive_int *);

recursive_int *first_not_full(recursive_int *);
recursive_int *last_not_full(recursive_int *);

recursive_int *recursive_int_last(recursive_int *);
recursive_int *recursive_int_set_last(recursive_int *, recursive_int *);

recursive_int *recursive_int_depth(recursive_int *);
recursive_int *recursive_int_revert(recursive_int *);

#endif