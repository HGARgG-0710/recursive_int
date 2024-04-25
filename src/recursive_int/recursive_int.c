#include "../include/recursive_int/recursive_int.h"

recursive_int *recursive_int_add(recursive_int *dest, recursive_int *summand)
{
	if (!dest->ri)
		dest->ri = summand;
	else
		recursive_int_add(dest->ri, summand);
	return dest;
};

recursive_int *recursive_int_add_i(recursive_int *dest, long long summand)
{
	recursive_int *to_recursive = recursive_int_from_ll(summand),
				  *added = recursive_int_add(dest, to_recursive);
	free_recursive_int(to_recursive);
	return added;
}

bool recursive_int_sign(recursive_int *ri)
{
	recursive_int *optimized = recursive_int_optimize(ri);
	const bool sign = optimized->value >= 0;
	free_recursive_int(optimized);
	return sign;
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
