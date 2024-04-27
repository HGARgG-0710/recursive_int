#ifndef RECURSIVE_INT_PRINT
#define RECURSIVE_INT_PRINT

#include <string.h>
#include <math.h>
#include "base.h"

wchar_t *string_reverse(wchar_t *);
wchar_t *base_representation(long long number, unsigned short base);

wchar_t *symbolic_addition(wchar_t *, wchar_t *);
wchar_t *symbolic_plus(wchar_t *, wchar_t *, unsigned long);

void recursive_int_print(recursive_int *, unsigned short base);
void recursive_int_print_sum(recursive_int *, unsigned short base);

#endif
