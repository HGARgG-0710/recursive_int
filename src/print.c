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
		final[0] = "-";
		strcat(final, absres);
		free(absres);
		return final;
	}
	const size_t pos = (size_t)(floor(log(number) / log(base)));
	wchar_t *buffer = (wchar_t *)malloc(sizeof(wchar_t) * pos);

	for (size_t i = 0; i < pos; i++)
	{
		const unsigned short remainder = number % (long long)base;
		buffer[i] = 32 + remainder;
		number -= remainder;
		number /= base;
	}

	wchar_t *reversed = string_reverse(buffer);
	free(buffer);
	buffer = reversed;

	return buffer;
}

wchar_t *symbolic_addition(wchar_t *a, wchar_t *b)
{
	// TODO: implement;
}

wchar_t *symbolic_plus(wchar_t *a, wchar_t *b, unsigned long coeff)
{
	// ! Concatenate one-by-one using either + or '-' (depending on the sign), AND by checking for repetitions (add integer-factors at the front);
}

// TODO: REFACTOR THOSE USING A MACRO...;
void recursive_int_print(recursive_int *ri, unsigned short base)
{
	recursive_int *currri = ri;
	wchar_t *final = base_representation(currri->value, base);
	while (currri->ri)
	{
		currri = currri->ri;
		wchar_t *next = base_representation(currri->value, base);
		wchar_t *copy = final;
		final = symbolic_addition(final, next);
		free(copy);
	}
	// 	TODO: print out the value;
}
void recursive_int_print_sum(recursive_int *ri, unsigned short base)
{
	recursive_int *currri = ri;
	wchar_t *final = base_representation(currri->value, base);
	unsigned long coeff = 1;

	while (currri->ri)
	{
		currri = currri->ri;
		wchar_t *next = base_representation(currri->value, base);
		coeff = (next == final) * (coeff) + 1;
		wchar_t *copy = final;
		final = symbolic_plus(final, next, coeff);
		free(copy);
	}
	// TODO: print out the value...; 
}