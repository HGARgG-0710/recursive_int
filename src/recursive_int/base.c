#include "../include/recursive_int/base.h"

recursive_int *alloc_recursive_int(long long value, recursive_int *subri)
{
	recursive_int *ri = (recursive_int *)malloc(sizeof(recursive_int));
	ri->value = value;
	ri->ri = subri;
	return ri;
}

recursive_int *free_recursive_int(recursive_int *ri)
{
	if (!ri)
		return true;
	if (ri->ri)
	{
		free_recursive_int(ri->ri);
		ri->ri = false;
	}
	free(ri);
	return false;
}

// * For optimization, one can do 'a = alloc_recursive_int(); ac = recursive_int_copy(a); a = free_recursive_int(a); a = &ac; ac = false;' to ensure that a given recursive_int is optimized;
// ! ADD THIS AS A MACRO! [add 'macros.c' file with them...];
recursive_int *recursive_int_copy(recursive_int *ri)
{
	return alloc_recursive_int(ri->value, ri->ri ? recursive_int_copy(ri->ri) : 0);
};

recursive_int *recursive_int_from_ll(long long value)
{
	return alloc_recursive_int(value, false);
}

recursive_int *recursive_int_inc(recursive_int *ri)
{
	if (LLONG_MAX == ri->value)
		return alloc_recursive_int(1, ri);
	++ri->value;
	return ri;
}
recursive_int *recursive_int_dec(recursive_int *ri)
{
	if (LLONG_MIN == ri->value)
		return alloc_recursive_int(-1, ri);
	--ri->value;
	return ri;
}

bool recursive_int_llfit(recursive_int *ri)
{
	if (!ri->ri)
		return true;
	if (!(ri->value >= 0 ? LLONG_MAX - ri->value >= ri->ri->value : LLONG_MIN - ri->value <= ri->ri->value))
		return false;
	recursive_int *intersum = alloc_recursive_int(ri->value + ri->ri->value, ri->ri->ri);
	const bool fits = recursive_int_llfit(intersum);
	free_recursive_int(intersum);
	return fits;
}

void recursive_int_abs(recursive_int *ri)
{
	ri->value = llabs(ri->value);
	if (ri->ri)
		recursive_int_abs(ri->ri);
}

void recursive_int_addinv(recursive_int *ri)
{
	ri->value = -ri->value;
	if (ri->ri)
		recursive_int_addinv(ri);
}

// ! Generalize these two ['get_positive' and 'get_negative']with a macro...
recursive_int *get_positive(recursive_int *ri)
{
	if (ri->value < 0)
		return get_positive(ri->value);
	recursive_int *positive = alloc_recursive_int(ri->value, get_positive(ri->ri));
	return positive;
}

recursive_int *get_negative(recursive_int *ri)
{
	if (ri->value >= 0)
		return get_negative(ri->value);
	recursive_int *negative = alloc_recursive_int(ri->value, get_negative(ri->ri));
	return negative;
}

recursive_int *recursive_zero()
{
	return recursive_int_from_ll(0);
}

recursive_int *first_not_full(recursive_int *ri)
{
	while ((ri->value == LLONG_MAX || ri->value == LLONG_MIN) && ri->ri)
		ri = ri->ri;
	return ri;
}

recursive_int *last_not_full(recursive_int *ri)
{
	while ((ri->value == LLONG_MAX || ri->value == LLONG_MIN) && ri->ri)
		ri = ri->ri;
	recursive_int *ri_p = ri;
	while (ri_p->ri)
	{
		ri_p = ri_p->ri;
		if (ri_p->value != LLONG_MAX && ri_p->value != LLONG_MIN)
			ri = ri_p;
	}
	return ri;
}