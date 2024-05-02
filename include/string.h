#ifndef RECURSIVE_INT_STRING
#define RECURSIVE_INT_STRING

#include <wchar.h>
#include <stdlib.h>

// todo: write documentation for the module...; 

wchar_t *alloc_str(size_t);
wchar_t *str_append(wchar_t *, long long newelems, wchar_t);
wchar_t *str_prepend(wchar_t *, long long newelems, wchar_t);

#endif
