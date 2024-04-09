#include <limits.h>
#include <stdlib.h>

#include "recursive_int.h"

// * 'copy' is made specifically for optimization purposes; One can do 'a = alloc_recursive_int(); ac = recursive_int_copy(a); a = free_recursive_int(a); a = &ac; ac = false;' to ensure that a given recursive_int is optimized;
// ! ADD AS A MACRO! [add 'macros.c' file with them...];
recursive_int *recursive_int_copy(recursive_int *ri)
{
	return recursive_int_optimize(alloc_recursive_int(ri->value, ri->ri ? recursive_int_copy(ri->ri) : 0));
};

recursive_int *recursive_int_from_ll(long long value)
{
	return alloc_recursive_int(value, false);
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
		return true;
	if (ri->ri)
	{
		free_recursive_int(ri->ri);
		ri->ri = false;
	}
	free(ri);
	return false;
}

recursive_int *recursive_int_add(recursive_int *dest, recursive_int *summand)
{
	if (!dest->ri)
		dest->ri = summand;
	else
		recursive_int_add(dest->ri, summand);
	return dest;
};

recursive_int *recursive_int_diff(recursive_int *dest, recursive_int *origin)
{
	recursive_int_addinv(origin); 
	recursive_int* diffed = recursive_int_sum(dest, origin); 	
	recursive_int_addinv(origin); 	
	return diffed; 
}

recursive_int *recursive_int_sum(recursive_int *dest, recursive_int *origin)
{
	// ! previously - addition code; re-do to make a downwards path...;
	// long long currval;

	// // ? Make into a macro? [reappers twice throughout...];
	// const bool sign = summand->value >= 0;
	// const long long limit = sign ? LLONG_MAX : LLONG_MIN;

	// recursive_int *(*change)(recursive_int *) = sign ? recursive_int_inc : recursive_int_dec;

	// while (true)
	// {
	// 	if (currval == summand->value && summand->ri)
	// 	{
	// 		dest = recursive_int_add(dest, summand->ri);
	// 		break;
	// 	}
	// 	currval += sign;
	// 	dest = change(dest);
	// }
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

recursive_int *recursive_int_add_i(recursive_int *dest, long long summand)
{
	recursive_int *to_recursive = recursive_int_from_ll(summand),
				  *added = recursive_int_add(dest, to_recursive);
	free_recursive_int(to_recursive);
	return added;
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

// * conducts memory-wise optimization of a rec-int [by default, they're unoptimized after operations, copying can be done for optimization];
recursive_int *recursive_int_optimize(recursive_int *ri)
{
	if (!ri || !ri->ri)
		return ri;
	recursive_int *negative = get_negative(ri),
				  *positive = get_positive(ri);
	recursive_int *clash = recursive_int_minimize(recursive_int_diff(positive, negative));
	positive = free_recursive_int(positive);
	negative = free_recursive_int(negative);
	return clash;
};

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

void recursive_int_abs(recursive_int *ri)
{
	ri->value = llabs(ri->value);
	if (ri->ri)
		recursive_int_abs(ri->ri);
}

bool recursive_int_sign(recursive_int *ri)
{
	recursive_int *optimized = recursive_int_optimize(ri);
	const bool sign = optimized->value >= 0;
	free_recursive_int(optimized);
	return sign;
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

void recursive_int_addinv(recursive_int *ri)
{
	ri->value = -ri->value;
	if (ri->ri)
		recursive_int_addinv(ri);
}

bool recursive_int_greater(recursive_int *a, recursive_int *b)
{
	recursive_int *acopy = recursive_int_diff(recursive_int_copy(a), recursive_int_copy(b));
	const bool is_greater = acopy->value >= 0;
	free_recursive_int(acopy);
	return is_greater;
}

bool recursive_int_equal(recursive_int *a, recursive_int *b)
{
	recursive_int *opa = recursive_int_optimize(a),
				  *opb = recursive_int_optimize(b);
	const bool equal = recursive_int_equal_optimized(a, b);
	free_recursive_int(opa);
	free_recursive_int(opb);
	return equal;
}
bool recursive_int_equal_optimized(recursive_int *a, recursive_int *b)
{
	if (!a != !b || a->value != b->value)
		return false;
	return recursive_int_equal_optimized(a->ri, b->ri);
}

recursive_int *recursive_int_mult(recursive_int *dest, recursive_int *origin)
{
	if (!recursive_int_equal(origin, 0))
	{
		// TODO: fix the 'copy'; Optimizing every time was A BAD idea; it should ONLY be done when needed for performance/optimization reasons...; ALSO - one should [as a rule] refrain from memory-optimization as it is costly;
		// ! OPTIMIZE WHERE IT'S STRATEGIC! Without optimization, certain algortihms cannot be implemented desireably [from interface standpoint]; So, do it only when absolutely necessary;
		// ? The code requires a thorough run-through to determine those places pin-pointedly...;
		recursive_int *origcopy = recursive_int_copy(origin);
		const bool sign = origcopy->value >= 0;
		recursive_int *destcopy = recursive_int_copy(dest);
		if (!sign)
			recursive_int_addinv(destcopy);
		recursive_int *(*change)(recursive_int *) = sign ? recursive_int_dec : recursive_int_inc;
		while (!recursive_int_equal(origcopy, 0))
		{
			change(origcopy);
			recursive_int_add(dest, destcopy);
		}
		return dest;
	}
	free_recursive_int(dest);
	// ! DO THIS MORE OFTEN THROUGHOUT THE CODE!!! [in some places, one fears, lack of this causes freed objects to go missing instead of getting replaced with new ones...]; 
	*dest = *recursive_zero();
	return dest;
}

recursive_int *recursive_zero()
{
	return recursive_int_from_ll(0);
}