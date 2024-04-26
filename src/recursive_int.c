#include "../include/recursive_int.h"

recursive_int *recursive_int_add(recursive_int *dest, recursive_int *summand)
{
	recursive_int *subdest = dest;
	while (subdest->ri)
		subdest = subdest->ri;
	subdest->ri = summand;
	return dest;
};

recursive_int *recursive_int_add_i(recursive_int *dest, long long summand)
{
	return recursive_int_add(dest, recursive_int_from_ll(summand));
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
	recursive_int *bc = recursive_int_copy(b);
	recursive_int *acopy = recursive_int_diff(recursive_int_copy(a), bc);
	const bool is_greater = acopy->value >= 0;
	free_recursive_int(bc);
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
	recursive_int *opdest = recursive_int_optimize(dest),
				  *oporig = recursive_int_optimize(origin);

	if (oporig->ri < 0)
	{
		opdest = recursive_int_addinv(opdest);
		oporig = recursive_int_addinv(oporig);
	}

	while (!optimized_is_zero(oporig))
	{
		oporig->value -= 1;
		while (!oporig->value && oporig->ri)
			oporig = oporig->ri;
		recursive_int *destcopy = recursive_int_copy(opdest);
		dest = recursive_int_sum(dest, destcopy);
	}

	return opdest;
}