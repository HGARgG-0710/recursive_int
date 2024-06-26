// ^ IDEA: create a typedef 'typedef long long symmetric_long;', then write a function for it - it'd cut the 'LLONG_MIN' from typical 'long long' by means of subtracting one (effectively: (x) => x - (x == LLONG_MIN))
// * only question is - where to store the type...;

#include "../include/base.h"

#define interloop(CHECK_OPERATOR)           \
	while (interri->value CHECK_OPERATOR 0) \
	{                                       \
		if (!interri->ri)                   \
			goto out;                       \
		interri = interri->ri;              \
	}

#define get_signed(NAME, CHECK_OPERATOR)                   \
	recursive_int *get_##NAME(recursive_int *ri)           \
	{                                                      \
		recursive_int *interri = ri;                       \
		recursive_int *sought = alloc_recursive_int(0, 0); \
		recursive_int *temppos = sought;                   \
		if (interri->ri)                                   \
		{                                                  \
			interloop(CHECK_OPERATOR);                     \
			temppos->value = interri->value;               \
		}                                                  \
		while (interri->ri)                                \
		{                                                  \
			interri = interri->ri;                         \
			interloop(CHECK_OPERATOR);                     \
			temppos->ri = recursive_int_from_ll(0);        \
			temppos = temppos->ri;                         \
			temppos->value = interri->value;               \
		}                                                  \
	out:                                                   \
		return sought;                                     \
	}

#define get_increment(NAME, CHECK_OPERATOR, SIGN, LIMIT)                \
	recursive_int *recursive_int_##NAME(recursive_int *ri, long long v) \
	{                                                                   \
		v = SIGN llabs(v);                                              \
		const bool insidebounds = ri->value CHECK_OPERATOR(LIMIT - v);  \
		ri->value = insidebounds ? ri->value + v : LIMIT;               \
		v = insidebounds ? 0 : -((LIMIT - v) - ri->value);              \
		if (v)                                                          \
			return alloc_recursive_int(v, ri);                          \
		return ri;                                                      \
	}

long long inc(long long v, long long a)
{
	return v + a;
}

long long dec(long long v, long long a)
{
	return v - a;
}

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
		return false;
	while (ri->ri)
	{
		recursive_int *r = ri->ri;
		free(ri);
		ri = r;
	}
	free(ri);
	return false;
}

recursive_int *recursive_int_copy(recursive_int *ri)
{
	recursive_int *res = alloc_recursive_int(ri->value, 0);
	recursive_int *tempres = res;
	while (ri->ri)
	{
		ri = ri->ri;
		tempres->ri = alloc_recursive_int(ri->value, 0);
		tempres = tempres->ri;
	}
	return res;
};

recursive_int *recursive_int_from_ll(long long value)
{
	return alloc_recursive_int(value, false);
}

get_increment(inc, <=, , LLONG_MAX);
get_increment(dec, >=, -, LLONG_MIN + 1);

recursive_int *recursive_int_abs(recursive_int *ri)
{
	recursive_int *tempri = ri;
	tempri->value = llabs(tempri->value);
	while (tempri->ri)
	{
		tempri = tempri->ri;
		tempri->value = llabs(tempri->value);
	}
	return ri;
}

recursive_int *recursive_int_addinv(recursive_int *ri)
{
	recursive_int *tempri = ri;
	tempri->value = -tempri->value;
	while (tempri->ri)
	{
		tempri = tempri->ri;
		tempri->value = -tempri->value;
	}
	return ri;
}

get_signed(positive, <=);
get_signed(negative, >=);

recursive_int *recursive_zero()
{
	return recursive_int_from_ll(0);
}

recursive_int *first_not_full(recursive_int *ri)
{
	while ((ri->value == LLONG_MAX || ri->value <= LLONG_MIN + 1) && ri->ri)
		ri = ri->ri;
	if (ri->value == LLONG_MAX || ri->value <= LLONG_MIN + 1)
		return false;
	return ri;
}

recursive_int *last_not_full(recursive_int *ri)
{
	while ((ri->value == LLONG_MAX || ri->value <= LLONG_MIN + 1) && ri->ri)
		ri = ri->ri;
	recursive_int *ri_p = ri;
	while (ri_p->ri)
	{
		ri_p = ri_p->ri;
		if (ri_p->value != LLONG_MAX && ri_p->value > LLONG_MIN + 1)
			ri = ri_p;
	}
	return ri;
}

recursive_int *recursive_int_last(recursive_int *ri)
{
	while (ri->ri)
		ri = ri->ri;
	return ri;
}
recursive_int *recursive_int_set_last(recursive_int *ri, recursive_int *newlast)
{
	if (!ri->ri)
		return ri;
	while (ri->ri->ri)
		ri = ri->ri;
	recursive_int *discarded = ri->ri;
	ri->ri = newlast;
	return discarded;
}

// TODO: optimize... [use a single 'long long' instead of this '1'];
recursive_int *recursive_int_depth(recursive_int *ri)
{
	recursive_int *depth = recursive_int_from_ll(1);
	while (ri->ri)
	{
		recursive_int_inc(depth, 1);
		ri = ri->ri;
	}
	return depth;
}

recursive_int *recursive_int_revert(recursive_int *ri)
{
	recursive_int *copy = recursive_int_copy(ri);
	recursive_int *last = recursive_int_last(copy);

	recursive_int *curr = copy;
	recursive_int *currlast = false;
	recursive_int *next;
	recursive_int *r = ri;

	while (r->ri && curr != last)
	{
		next = curr->ri;
		last->ri = curr;
		curr->ri = currlast;
		currlast = curr;
		curr = next;
		recursive_int *_r = r->ri;
		free(r);
		r = _r;
	}

	*ri = *last;

	return ri;
}