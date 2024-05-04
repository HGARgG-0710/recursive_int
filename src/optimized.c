// ^ IDEA: create the general 'non-optimized' algorithms that would rely upon dynamic decision of 'directions' of change (note - the 'optimized' version still stays as it is faster (an O(1) operations turn into O(n)); the general one goes into either 'base' or 'recursive_int');

#include "../include/optimized.h"

// ! leaks [think about what to do with them - perhaps, restructure the way that certain methods work? (to make freeing memory easier)];
// * conducts memory-wise optimization of a rec-int [by default, they're unoptimized after operations, copying can be done for optimization];
recursive_int *recursive_int_optimize(recursive_int *ri)
{
	if (!ri || !ri->ri)
		return ri;
	ri = de_zero(ri);
	return recursive_int_optimized_revert(
		recursive_int_minimize(
			recursive_int_sum(
				recursive_int_minimize(get_positive(ri)),
				recursive_int_minimize(get_negative(ri)))));
};

recursive_int *recursive_int_diff(recursive_int *dest, recursive_int *origin)
{
	return recursive_int_sum(dest, recursive_int_addinv(origin));
}

recursive_int *recursive_int_sum(recursive_int *dest, recursive_int *origin)
{
	const bool destSign = dest->value >= 0,
			   origSign = origin->value >= 0;
	const bool direction = destSign == origSign;

	if (direction)
	{
		recursive_int *(*change)(recursive_int *, long long) = origSign ? recursive_int_inc : recursive_int_dec;
		while (!optimized_is_zero(origin))
		{
			while (!origin->value)
				origin = origin->ri;
			dest = change(dest, origin->value);
			origin->value = 0;
		}
		return dest;
	}

	long long (*destChange)(long long, long long) = destSign ? dec : inc;
	long long (*origChange)(long long, long long) = origSign ? dec : inc;

	while (!optimized_is_zero(origin) && !optimized_is_zero(dest))
	{
		while (!origin->value && origin->ri)
			origin = origin->ri;
		while (!dest->value && dest->ri)
			dest = dest->ri;
		const long long destval = dest->value;
		const long long origval = origin->value;
		const bool largerabs = llabs(destval) > llabs(origval);
		dest->value = largerabs ? destChange(destval, llabs(origval)) : 0;
		origin->value = largerabs ? 0 : origChange(origval, llabs(destval));
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
	const long long LIMIT = sign ? LLONG_MAX : (LLONG_MIN + 1);
	bool (*compare)(long long, long long) = sign ? lesseroe : greateroe;

	recursive_int *topri = ri->value == LIMIT ? ri->ri : ri;
	recursive_int *ricurr;

	while (topri->ri)
	{
		ricurr = topri->ri;
		if (compare(topri->value, LIMIT - ricurr->value))
		{
			topri->value += ricurr->value;
			topri->ri = ricurr->ri;
			free(ricurr);
			continue;
		}
		ricurr->value = -((LIMIT - topri->value) - ricurr->value);
		topri->value = LIMIT;
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
		if (midri->ri)
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