#include "../include/optimized.h"

#define recursive_int_minimize_signed(LIMIT, SIGN)                        \
	if (!ri->ri)                                                          \
		return ri;                                                        \
	recursive_int *topri = ri->value == LIMIT ? ri->ri : ri;              \
	recursive_int *ricurr = topri->ri;                                    \
	while (ricurr->ri)                                                    \
	{                                                                     \
		ricurr = topri->ri;                                               \
		if (topri->value SIGN LIMIT - ricurr->value)                      \
		{                                                                 \
			topri->value += ricurr->value;                                \
			topri->ri = ricurr->ri;                                       \
			free(ricurr);                                                 \
			continue;                                                     \
		}                                                                 \
		const long long diff = -((LIMIT - topri->value) - ricurr->value); \
		topri->value = LIMIT;                                             \
		ricurr->value -= diff;                                            \
		topri = topri->ri;                                                \
	}                                                                     \
	return ri;

// * conducts memory-wise optimization of a rec-int [by default, they're unoptimized after operations, copying can be done for optimization];
recursive_int *recursive_int_optimize(recursive_int *ri)
{
	if (!ri || !ri->ri)
		return ri;
	recursive_int *negative = get_negative(ri),
				  *positive = get_positive(ri);
	recursive_int *clash =
		recursive_int_optimized_revert(
			recursive_int_minimize(
				de_zero(
					recursive_int_sum(positive, negative))));
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
			while (!origin->value)
				origin = origin->ri;
			dest = change(dest);
			origin->value = origSign ? origin->value - 1 : origin->value + 1;
		}
		return dest;
	}

	const long long maxval = destSign ? LLONG_MAX : LLONG_MIN;

	while (!optimized_is_zero(origin) && !optimized_is_zero(dest))
	{
		while (!origin->value)
			origin = origin->ri;
		while (dest->value == maxval)
			dest = dest->ri;
		dest->value = destSign ? dest->value + 1 : dest->value - 1;
		origin->value = origSign ? origin->value - 1 : origin->value + 1;
	}

	return optimized_is_zero(origin) ? dest : origin;
}

bool recursive_int_equal_optimized(recursive_int *a, recursive_int *b)
{
	while (a->ri && b->ri)
	{
		if (a->value != b->value)
			return false;
		a = a->ri;
		b = b->ri;
	}
	return !a->ri == !b->ri;
}

recursive_int *recursive_int_minize(recursive_int *ri)
{
	if (ri->value >= 0)
	{
		recursive_int_minimize_signed(LLONG_MAX, <=)
	}
	recursive_int_minimize_signed(LLONG_MIN, >=)
}

recursive_int *de_zero(recursive_int *ri)
{
	if (!ri->ri)
		return ri;
	recursive_int *topri = ri;
	recursive_int *r = topri->ri;
	while (!topri->value && topri->ri)
	{
		free(topri);
		topri = r;
		r = topri->ri;
	}
	return topri;
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