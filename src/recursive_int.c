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
	recursive_int *ac = recursive_int_copy(a),
				  *bc = recursive_int_copy(b);
	const bool is_greater = recursive_int_diff(ac, bc)->value >= 0;
	free_recursive_int(ac);
	free_recursive_int(bc);
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

// ! critical note: while this 'works', it's horribly inefficient. Instead (after having finished the 'print' properly) - transform to a 'wchar_t *' via 'print', then do a 'symbolic multiplication' (implement Karatsuba's, or some other fast-multiplication algorithm);
// ^ values around ~2*10^6 ALREADY cause the execution to take an inappropriately large amount of time...; Here, the speed is O(n^2), whereas the multiplication using symbols would reduce it to (at least) O(log(n)^2); 
// ^ note: also - not requiring to constantly allocate-deallocate inside the function would make the code clearer (again, the issue with memory-safety: the 'copy, not replace' principle);
// * The algorithms for addition and multiplication will ABSOLUTELY CHOKE on larger values...;
recursive_int *recursive_int_mult(recursive_int *dest, recursive_int *origin)
{
	recursive_int *opdest = recursive_int_optimize(dest),
				  *oporig = recursive_int_optimize(origin);

	if (oporig->value < 0)
	{
		opdest = recursive_int_addinv(opdest);
		oporig = recursive_int_addinv(oporig);
	}

	recursive_int *initcopy = recursive_int_copy(opdest);
	recursive_int *destcopy;

	--oporig->value;
	if (!oporig->value)
	{
		recursive_int *t = oporig->ri;
		free(oporig);
		oporig = t;
	}

	while (!optimized_is_zero(oporig))
	{
		--oporig->value;
		while (!oporig->value && oporig->ri)
			oporig = oporig->ri;
		destcopy = recursive_int_copy(initcopy);
		opdest = recursive_int_sum(opdest, destcopy);
		free_recursive_int(destcopy);
	}

	free_recursive_int(initcopy);

	return opdest;
}

bool is_zero(recursive_int *ri)
{
	recursive_int *opri = recursive_int_optimize(ri);
	const bool isZero = optimized_is_zero(opri);
	free_recursive_int(opri);
	return isZero;
}

bool recursive_int_llfit(recursive_int *ri)
{
	recursive_int *optimized = recursive_int_optimize(ri);
	const bool fits = !optimized->ri;
	free_recursive_int(optimized);
	return fits;
}