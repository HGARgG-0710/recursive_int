// TODO: write a notice in the documentation that this module is only made for purposes of debugging and is not meant to work for all the 'recursive_int's (some are too large to be represented using a char*);
// ^ IDEA: expand the library later, to include also:
// * 1. recursive_string - a recursive representation of string;
// * 2. (FAR) more optimized implementation structure from the standpoint of allocation (this is INCREDIBLY slow - user should be allowed to structure data not in a single 'long'/'char', but multiple - via 'long *' or 'char *').
// * 3. More optimized printing (not necesserily depending on the 'wchar_t' type);

#include "../include/print.h"

#define symbolic_abs(IDENTIFIER, COPY)              \
	IDENTIFIER = alloc_str(wcslen(IDENTIFIER) - 1); \
	wcsncpy(IDENTIFIER, COPY + 1, wcslen(COPY) - 1);

wchar_t *string_reverse(wchar_t *string)
{
	const size_t length = wcslen(string);
	wchar_t *reversed = alloc_str(length);
	for (size_t i = 0; i < length; ++i)
		reversed[i] = string[length - 1 - i];
	return reversed;
}

wchar_t *base_representation(long long number, unsigned short base)
{
	if (!number)
	{
		wchar_t *zero = alloc_str(1);
		zero[0] = 48;
		return zero;
	}
	if (number < 0)
	{
		wchar_t *absres = base_representation(llabs(number), base);
		wchar_t *final = negate(absres);
		// printf("\n\n\nNEG! %lld", number);
		// printf("\nABS-D; %lld", llabs(number));
		// printf("\nABSRES: %ls", absres);
		// printf("\nRESULT: %ls\n\n", final);
		free(absres);
		return final;
	}
	const size_t pos = (size_t)(floor(log(number) / log(base)));
	wchar_t *buffer = alloc_str(pos + 1);

	// printf("\n\nPOS! %lld", number);
	// printf("\nBASE: %d\n", base);

	for (size_t i = 0; i < 1 + pos; ++i)
	{
		const unsigned short remainder = number % base;
		// printf("? %d\n", remainder);
		buffer[pos - i] = (wchar_t)48 + remainder;
		number -= remainder;
		number /= base;
	}

	// printf("OUT: %ls\n", buffer);

	return buffer;
}

// TODO: does not work for cases when '|sub| > |total|' - doesn't change signs, just stops. Flaw of 'sub'.
wchar_t *symbolic_bit_sub(wchar_t *dest, wchar_t *add, size_t pos, unsigned short base)
{
	wchar_t *cadd = alloc_str(1);
	cadd[0] = add[wcslen(add) - 1];
	pos = wcslen(dest) - 1 - pos;
	// printf("\n\npos (sub): %lld", pos);
	// printf("\ndest (sub): %ls", dest);
	// printf("\nadd (sub): %ls", add);
	while (dest[pos] != 48 && *cadd > 48)
	{
		dest[pos]--;
		(*cadd)--;
	}
	if (*cadd > 48 && pos)
	{
		wchar_t *topsym = alloc_str(1);
		topsym[0] = (base - 1) + 48;
		dest = symbolic_bit_add(dest, topsym, wcslen(dest) - 1 - pos, base);
		dest = symbolic_bit_sub(dest, (wchar_t *)L"1", wcslen(dest) - pos, base);
		(*cadd)--;
		dest = symbolic_bit_sub(dest, cadd, wcslen(dest) - 1 - pos, base);
		free(topsym);
	}
	free(cadd);
	return dest;
}

wchar_t *symbolic_new_size(wchar_t *total, size_t length)
{
	const size_t prevlen = wcslen(total);
	total = str_append(total, length - prevlen, 48);
	for (size_t i = 0; i < length - prevlen; ++i)
		total = symbolic_right_shift(total);
	return total;
}

bool symbolic_greater(wchar_t *a, wchar_t *b)
{
	bool newsized_set = false;
	wchar_t *newsized;
	const size_t size = wcslen(a);

	if (size != wcslen(b))
	{
		const size_t maxsize = max(size, wcslen(b));
		newsized = symbolic_new_size(maxsize == size ? b : a, maxsize);
		if (maxsize == size)
			b = newsized;
		else
			a = newsized;
		newsized_set = true;
	}

	bool aneg = a[0] == '-',
		 bneg = b[0] == '-';
	if (aneg != bneg)
		return bneg;

	bool result = false;
	for (size_t i = aneg; i < size; ++i)
	{
		if (a[i] != b[i])
		{
			result = aneg ? a[i] < b[i] : a[i] > b[i];
			break;
		}
	}
	if (newsized_set)
		free(newsized);

	return result;
}

// TODO: fix this to allow multiple '-' (and resolving them...);
wchar_t *negate(wchar_t *a)
{
	return str_prepend(a, 1, (wchar_t)'-');
}

wchar_t *symbolic_subtraction(wchar_t *total, wchar_t *sub, unsigned short base)
{
	if (symbolic_greater(sub, total))
		return negate(symbolic_subtraction(sub, total, base));
	const size_t length = wcslen(sub);
	if (length > wcslen(total))
		total = symbolic_new_size(total, length);
	wchar_t *isolated = alloc_str(1);
	for (size_t i = 0; i < length; ++i)
	{
		isolated[0] = sub[length - 1 - i];
		total = symbolic_bit_sub(total, isolated, i, base);
	}
	free(isolated);
	return total;
}

// TODO: generalize these two - allow multiple position shifts... (would simplify some of the code that uses them a lot...);
wchar_t *symbolic_right_shift(wchar_t *dest)
{
	const size_t l = wcslen(dest);
	for (size_t i = l - 1; i > 0; --i)
		dest[i] = dest[i - 1];
	dest[0] = 48;
	return dest;
}
wchar_t *symbolic_left_shift(wchar_t *dest)
{
	for (size_t i = 0; i < wcslen(dest) - 1; ++i)
		dest[i] = dest[i + 1];
	dest[wcslen(dest) - 1] = 48;
	return dest;
}

// ? REFACTOR? the bits with 'realloc', in particular...;
// ! generally - walk through the code, fix silliness... (too consumed by fixing allocation and null-terminated strings errors currently...);
wchar_t *symbolic_bit_add(wchar_t *dest, wchar_t *add, long long pos, unsigned short base)
{
	// printf("\n\npos (add): %lld", pos);
	// printf("\ndest (add): %ls", dest);
	// printf("\nadd (add): %ls", add);
	wchar_t *cadd = alloc_str(1);
	cadd[0] = add[wcslen(add) - 1];
	pos = wcslen(dest) - 1 - pos;
	if (pos < 0)
	{
		dest = str_append(dest, -pos, 48);
		// ? REWRITE - using plain loops, would be more efficient than this...;
		for (; pos < 0; ++pos)
			symbolic_right_shift(dest);
	}
	while (*cadd > 48 && dest[pos] < base + 48)
	{
		dest[pos]++;
		(*cadd)--;
	}
	if (dest[pos] >= base + 48)
	{
		dest[pos] = *cadd;
		dest = symbolic_bit_add(dest, (wchar_t *)L"1", (wcslen(dest) - 1 - pos) + 1, base);
	}
	free(cadd);
	return dest;
}

wchar_t *symbolic_addition(wchar_t *a, wchar_t *b, unsigned short base)
{
	const bool aneg = a[0] == '-', bneg = b[0] == '-';

	if (aneg != bneg)
	{
		wchar_t *ca = a, *cb = b;
		wchar_t *c = aneg ? a : b,
				*cc = aneg ? ca : cb,
				*d = aneg ? b : a;
		symbolic_abs(c, cc);
		wchar_t *subtracted = symbolic_subtraction(d, c, base);
		free(c);
		return subtracted;
	}

	const size_t length = min(wcslen(b), wcslen(a));
	wchar_t *curr = length == wcslen(a) ? a : b;
	wchar_t *dest = curr == a ? b : a;
	wchar_t *isolated = alloc_str(1);
	for (size_t i = 0; i < length - aneg; ++i)
	{
		isolated[0] = curr[length - 1 - i];
		dest = symbolic_bit_add(dest, isolated, i, base);
	}
	free(isolated);
	return dest;
}

// TODO: later - generalize to the 'coeff' idea (represent the repeating sums as products) - this'll require a structure with wchar_t** pointer;
wchar_t *symbolic_plus(wchar_t *a, wchar_t *b)
{
	const bool positive = b[0] != (wchar_t)'-';
	wchar_t *plused = alloc_str(wcslen(a) + positive + wcslen(b));
	wcscpy(plused, a);
	if (positive)
		wcscpy(plused + wcslen(a), (wchar_t *)L"+");
	wcscpy(plused + wcslen(a) + positive, b);
	return plused;
}

wchar_t *recursive_int_print(recursive_int *ri, unsigned short base)
{
	wchar_t *final = base_representation(ri->value, base);
	wchar_t *next;

	while (ri->ri)
	{
		ri = ri->ri;
		next = base_representation(ri->value, base);
		final = symbolic_addition(final, next, base);
		printf("\nCURRSUM: %ls", final);
	}
	printf("\nCURRSUM: %ls\n", final);

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
		final = symbolic_plus(final, next);
		free(copy);
		free(next);
	}

	return final;
}