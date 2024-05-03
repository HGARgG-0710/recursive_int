#ifndef RECURSIVE_INT_PRINT
#define RECURSIVE_INT_PRINT

#include <locale.h>
#include <string.h>
#include <math.h>

#include "base.h"
#include "string.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))


wchar_t *negate(wchar_t *a);
bool symbolic_greater(wchar_t * a, wchar_t * b);

wchar_t *string_reverse(wchar_t *);
wchar_t *base_representation(long long number, unsigned short base);

wchar_t *symbolic_right_shift(wchar_t *dest);
wchar_t *symbolic_left_shift(wchar_t *dest);

wchar_t *symbolic_bit_add(wchar_t *dest, wchar_t *add, long long pos, unsigned short base);
wchar_t *symbolic_bit_sub(wchar_t *dest, wchar_t *add, size_t pos, unsigned short base);

wchar_t *symbolic_addition(wchar_t *, wchar_t *, unsigned short base);
wchar_t *symbolic_subtraction(wchar_t *total, wchar_t *sub, unsigned short base);
wchar_t *symbolic_plus(wchar_t *, wchar_t *);

wchar_t *recursive_int_print(recursive_int *, unsigned short base);
wchar_t *recursive_int_print_sum(recursive_int *, unsigned short base);

#endif
