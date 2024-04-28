// TODO: write a notice in the documentation that this module is only made for purposes of debugging and is not meant to work for all the 'recursive_int's (some are too large to be represented using a char*);
// ^ IDEA: expand the library later, to include also:
// * 1. recursive_string - a recursive representation of string;
// * 2. (FAR) more optimized implementation structure from the standpoint of allocation (this is INCREDIBLY slow - user should be allowed to structure data not in a single 'long'/'char', but multiple - via 'long *' or 'char *').
// * 3. More optimized printing (not necesserily depending on the 'wchar_t' type);

#include "../include/print.h"

wchar_t *string_reverse(wchar_t *string)
{
	wchar_t *reversed = (wchar_t *)malloc(sizeof(string));
	const size_t length = wcslen(string);
	for (size_t i = length - 1; i >= 0; ++i)
		reversed[i] = string[length - 1 - i];
	return reversed;
}

wchar_t *base_representation(long long number, unsigned short base)
{
	if (number < 0)
	{
		const wchar_t *absres = base_representation(llabs(number), base);
		wchar_t *final = (wchar_t *)malloc(sizeof(wchar_t) * (1 + sizeof(absres) / sizeof(wchar_t)));
		final[0] = (wchar_t) "-";
		wcscat(final, absres);
		free(absres);
		return final;
	}
	const size_t pos = (size_t)(floor(log(number) / log(base)));
	wchar_t *buffer = (wchar_t *)malloc(sizeof(wchar_t) * pos);

	for (size_t i = 0; i < pos; ++i)
	{
		const unsigned short remainder = number % (long long)base;
		buffer[i] = 48 + remainder;
		number -= remainder;
		number /= base;
	}

	wchar_t *reversed = string_reverse(buffer);
	free(buffer);
	buffer = reversed;

	return buffer;
}

wchar_t *symbolic_bit_sub(wchar_t *dest, wchar_t *add, size_t pos, unsigned short base)
{
	wchar_t *cadd = (wchar_t *)malloc(sizeof(wchar_t));
	wcscpy(cadd, add);
	while (dest[pos] != 48 && *cadd > 48)
	{
		dest[pos]--;
		*cadd--;
	}
	if (*cadd > 48)
	{
		symbolic_bit_add(dest, (base - 1) + 48, pos, base);
		symbolic_bit_sub(dest, "1", pos + 1, base);
		symbolic_bit_sub(dest, cadd, pos, base);
	}
	free(cadd);
	return dest;
}

wchar_t *symbolic_subtraction(wchar_t *total, wchar_t *sub, unsigned short base)
{
	const size_t length = wcslen(sub);
	const wchar_t *dest = total;
	for (size_t i = 0; i < length; ++i)
		symbolic_bit_sub(dest, sub[i], i, base);
	return dest;
}

// todo: this algorithm does not take in account the fact that this thing is reversed!
// ! FIX THIS! [look for this bug in the other methods as well];
wchar_t *symbolic_bit_add(wchar_t *dest, wchar_t *add, size_t pos, unsigned short base)
{
	wchar_t *cadd = (wchar_t *)malloc(sizeof(wchar_t));
	wcscpy(cadd, add);
	while (*cadd > 48 && dest[pos] < base - 48)
	{
		dest[pos]++;
		*cadd--;
	}
	if (cadd > 48)
		symbolic_bit_add(dest, (wchar_t) "1", pos + 1, base);
	free(cadd);
	return dest;
}

wchar_t *symbolic_addition(wchar_t *a, wchar_t *b, unsigned short base)
{
	const bool aneg = a[0] == "-", bneg = b[0] == "-";
	if (aneg != bneg)
	{
		wchar_t *ca = a, *cb = b;
		// TODO: macro... refactor...;
		if (aneg)
		{
			a = (wchar_t *)malloc(sizeof(a) - 1);
			wcsncpy(a, ca + 1, wcslen(ca) - 1);
		}
		else
		{
			b = (wchar_t *)malloc(sizeof(b) - 1);
			wcsncpy(b, cb + 1, wcslen(cb) - 1);
		}
		wchar_t *subtracted = symbolic_subtraction(aneg ? b : a, aneg ? a : b, base);
		free(aneg ? a : b);
		return subtracted;
	}

	const size_t length = min(wcslen(b), wcslen(a));
	const wchar_t *curr = length == wcslen(a) ? a : b;
	const wchar_t *dest = curr == a ? b : a;
	for (size_t i = 0; i < length - aneg; ++i)
		symbolic_bit_add(dest, curr[i], i, base);
	return dest;
}

// TODO: later - generalize to the 'coeff' idea (represent the repeating sums as products) - this'll require a structure with wchar_t** pointer;
wchar_t *symbolic_plus(wchar_t *a, wchar_t *b, unsigned short base)
{
	const bool positive = b[0] != "-";
	wchar_t *plused = (wchar_t *)malloc(sizeof(a) + positive * sizeof(wchar_t) + sizeof(b));
	wcscpy(plused, a);
	if (positive)
		wcscat(plused, "+");
	wcscat(plused, b);
	return plused;
}

wchar_t *recursive_int_print(recursive_int *ri, unsigned short base)
{
	wchar_t *final = base_representation(ri->value, base);

	while (ri->ri)
	{
		ri = ri->ri;
		wchar_t *next = base_representation(ri->value, base);
		final = symbolic_addition(final, next, base);
		free(next);
	}

	return final;
}
wchar_t *recursive_int_print_sum(recursive_int *ri, unsigned short base)
{
	wchar_t *final = base_representation(ri->value, base);

	while (ri->ri)
	{
		ri = ri->ri;
		wchar_t *next = base_representation(ri->value, base);
		wchar_t *copy = final;
		final = symbolic_plus(final, next, base);
		free(copy);
		free(next);
	}

	return final;
}