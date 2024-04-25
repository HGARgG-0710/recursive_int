#include "../include/base.h"
#include "../include/optimized.h"

// * conducts memory-wise optimization of a rec-int [by default, they're unoptimized after operations, copying can be done for optimization];
recursive_int *recursive_int_optimize(recursive_int *ri)
{
	if (!ri || !ri->ri)
		return ri;
	recursive_int *negative = get_negative(ri),
				  *positive = get_positive(ri);
	recursive_int *clash = recursive_int_optimized_revert(recursive_int_minimize(de_zero(recursive_int_sum(positive, negative))));
	free_recursive_int(negative);
	return clash;
};

recursive_int *recursive_int_diff(recursive_int *dest, recursive_int *origin)
{
	recursive_int_addinv(origin);
	recursive_int *diffed = recursive_int_sum(dest, origin);
	recursive_int_addinv(origin);
	return diffed;
}

recursive_int *recursive_int_sum(recursive_int *dest, recursive_int *origin)
{
	const bool destSign = dest->value >= 0,
			   origSign = origin->value >= 0;
	const bool direction = destSign == origSign;

	if (direction)
	{
		const recursive_int *(*change)(recursive_int *) = origSign ? recursive_int_inc : recursive_int_dec;
		while (!optimized_is_zero(origin))
		{
			if (!origin->value)
				return recursive_int_sum(dest, origin->ri);
			dest = change(dest);
			origin->value = origSign ? origin->value - 1 : origin->value + 1;
		}
		return dest;
	}

	const long long maxval = destSign ? LLONG_MAX : LLONG_MIN;

	while (!optimized_is_zero(origin) && !optimized_is_zero(dest))
	{
		if (!origin->value)
			return recursive_int_sum(dest, origin->ri);
		if (dest->value == maxval)
			return recursive_int_sum(dest->ri, origin);
		dest->value = destSign ? dest->value + 1 : dest->value - 1;
		origin->value = origSign ? origin->value - 1 : origin->value + 1;
	}

	return optimized_is_zero(origin) ? dest : origin;
}

bool recursive_int_equal_optimized(recursive_int *a, recursive_int *b)
{
	if (!a->ri != !b->ri || a->value != b->value)
		return false;
	return recursive_int_equal_optimized(a->ri, b->ri);
}

recursive_int *recursive_int_minize(recursive_int *ri)
{
	if (ri->value >= 0)
		return recursive_int_minize_positive(ri);
	return recursive_int_minize_negative(ri);
}

recursive_int *de_zero(recursive_int *ri)
{
	recursive_int *r = ri->ri;
	if (!ri->value)
		free(ri);
	return recursive_int_minimize(r);
}

recursive_int *recursive_int_minize_positive(recursive_int *ri)
{
	if (!ri->ri)
		return ri;
	if (ri->value == LLONG_MAX)
		return recursive_int_minize_positive(ri->ri);
	recursive_int *ricurr;
	while (ri->value + ricurr->value < LLONG_MAX)
	{
		ricurr = ri->ri;
		ri->value += ricurr->value;
		ri->ri = ricurr->ri;
		free(ricurr);
	}

	return recursive_int_minize_positive(ri->ri);
}
recursive_int *recursive_int_minize_negative(recursive_int *ri)
{
	if (!ri->ri)
		return ri;
	if (ri->value == LLONG_MAX)
		return recursive_int_minize_positive(ri->ri);
	recursive_int *ricurr;
	while (ri->value + ricurr->value > LLONG_MIN)
	{
		ricurr = ri->ri;
		ri->value += ricurr->value;
		ri->ri = ricurr->ri;
		free(ricurr);
	}

	return recursive_int_minize_positive(ri->ri);
}

bool optimized_is_zero(recursive_int *ri)
{
	return ri->value == 0 && !ri->ri;
}

recursive_int *recursive_int_optimized_revert(recursive_int *ri)
{
	if (!ri->ri)
		return ri;
	recursive_int *last = recursive_int_set_last(ri, ri);
	recursive_int *newfirst = ri->ri;
	ri->ri = false;
	return newfirst;
}