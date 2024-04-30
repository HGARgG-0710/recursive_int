// ^ IDEA: create the general 'non-optimized' algorithms that would rely upon dynamic decision of 'directions' of change (note - the 'optimized' version still stays as it is faster (an O(1) operations turn into O(n)); the general one goes into either 'base' or 'recursive_int');

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

long long inc(long long v)
{
	return v + 1;
}

long long dec(long long v)
{
	return v - 1;
}

recursive_int *recursive_int_sum(recursive_int *dest, recursive_int *origin)
{
	const bool destSign = dest->value >= 0,
			   origSign = origin->value >= 0;
	const bool direction = destSign == origSign;

	long long (*origChange)(long long) = origSign ? dec : inc;

	if (direction)
	{
		recursive_int *(*change)(recursive_int *) = origSign ? recursive_int_inc : recursive_int_dec;
		while (!optimized_is_zero(origin))
		{
			while (!origin->value)
				origin = origin->ri;
			dest = change(dest);
			origin->value = origChange(origin->value);
		}
		return dest;
	}

	long long (*destChange)(long long) = destSign ? dec : inc;
	recursive_int_addinv(!destSign ? dest : origin);
	const long long maxval = destSign ? LLONG_MAX : LLONG_MIN;

	while (!optimized_is_zero(origin) && !optimized_is_zero(dest))
	{
		while (!origin->value && origin->ri)
			origin = origin->ri;
		while (dest->value == maxval && dest->ri)
			dest = dest->ri;
		dest->value = destChange(dest->value);
		origin->value = origChange(origin->value);
	}

	return optimized_is_zero(origin) ? dest : origin;
}

bool recursive_int_equal_optimized(recursive_int *a, recursive_int *b)
{
	if (a->value != b->value)
		return false;
	while (a->ri && b->ri)
	{
		a = a->ri;
		b = b->ri;
	}
	return !a->ri && !b->ri;
}

bool lesseroe(long long a, long long b)
{
	return a <= b;
}
bool greateroe(long long a, long long b)
{
	return a >= b;
}

recursive_int *recursive_int_minimize(recursive_int *ri)
{
	if (!ri->ri)
		return ri;

	const bool sign = ri->value >= 0;
	const long long LIMIT = sign ? LLONG_MAX : LLONG_MIN;
	bool (*compare)(long long, long long) = sign ? lesseroe : greateroe;

	recursive_int *topri = ri->value == LIMIT ? ri->ri : ri;
	recursive_int *ricurr = topri->ri;

	while (ricurr->ri)
	{
		ricurr = topri->ri;
		if (compare(topri->value, LIMIT - ricurr->value))
		{
			topri->value += ricurr->value;
			topri->ri = ricurr->ri;
			free(ricurr);
			continue;
		}
		const long long diff = -((LIMIT - topri->value) - ricurr->value);
		topri->value = LIMIT;
		ricurr->value -= diff;
		topri = topri->ri;
	}
	return ri;
}

recursive_int *de_zero(recursive_int *ri)
{
	if (!ri->ri)
		return ri;
	// * clearing zeros from the top (finding the top-ri to be returned);
	recursive_int *topri = ri;
	recursive_int *r = topri->ri;
	while (!topri->value && topri->ri)
	{
		free(topri);
		topri = r;
		r = topri->ri;
	}
	// * clearing the middle zeros;
	recursive_int *midri = r;
	recursive_int *concatri = topri;
	while (midri->ri)
	{
		if (!midri->value)
		{
			r = midri->ri;
			free(midri);
			midri = r;
			concatri->ri = midri;
		}
		concatri = concatri->ri;
		midri = midri->ri;
	}
	// * clearing the potentially missed last zero;
	if (!midri->value)
	{
		free(midri);
		concatri->ri = false;
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
	recursive_int *prevlast = recursive_int_set_last(ri, ri);
	prevlast->ri = ri->ri;
	ri->ri = false;
	return prevlast;
}