#include "../include/recursive_int/optimized.h"

// * conducts memory-wise optimization of a rec-int [by default, they're unoptimized after operations, copying can be done for optimization];
recursive_int *recursive_int_optimize(recursive_int *ri)
{
	if (!ri || !ri->ri)
		return ri;
	recursive_int *negative = get_negative(ri),
				  *positive = get_positive(ri);
	recursive_int_addinv(negative);
	recursive_int *clash = recursive_int_minimize(recursive_int_diff(positive, negative));
	positive = free_recursive_int(positive);
	negative = free_recursive_int(negative);
	return clash;
};

recursive_int *recursive_int_diff_pos_neg(recursive_int *dest, recursive_int *origin)
{
	recursive_int_addinv(origin);
	recursive_int *diffed = recursive_int_sum(dest, origin);
	recursive_int_addinv(origin);
	return diffed;
}

recursive_int *recursive_int_sum(recursive_int *dest, recursive_int *origin)
{
	
}

bool recursive_int_equal_optimized(recursive_int *a, recursive_int *b)
{
	if (!a != !b || a->value != b->value)
		return false;
	return recursive_int_equal_optimized(a->ri, b->ri);
}

// ! optimizes cases, when there is no sign alteration in terms...;
recursive_int *recursive_int_minize(recursive_int *ri)
{
	if (ri->value >= 0)
		return recursive_int_minize_positive(ri);
	return recursive_int_minize_negative(ri);
}

recursive_int *recursive_int_minize_positive(recursive_int *ri)
{
}
recursive_int *recursive_int_minize_negative(recursive_int *ri)
{
}