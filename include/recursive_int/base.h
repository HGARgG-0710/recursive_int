#ifndef RECURSIVE_INT_BASE
#define RECURSIVE_INT_BASE

#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct
{
	recursive_int *ri;
	long long value;
} recursive_int;

recursive_int *alloc_recursive_int(long long, recursive_int *);
recursive_int *free_recursive_int(recursive_int *);
recursive_int *recursive_int_copy(recursive_int *);

void recursive_int_abs(recursive_int *);
void recursive_int_addinv(recursive_int *);

recursive_int *recursive_int_inc(recursive_int *);
recursive_int *recursive_int_dec(recursive_int *);

recursive_int *recursive_zero();
bool recursive_int_llfit(recursive_int *);

recursive_int *get_negative(recursive_int *);
recursive_int *get_positive(recursive_int *);

recursive_int *first_not_full(recursive_int *);
recursive_int *last_not_full(recursive_int *); 

#endif