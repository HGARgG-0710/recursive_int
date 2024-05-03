// * Methods for working with strings

#include "../include/string.h"

wchar_t *alloc_str(size_t elems)
{
	wchar_t *strpointer = (wchar_t *)malloc(sizeof(wchar_t) * (1 + elems));
	strpointer[elems] = 0;
	return strpointer;
}

// * creates a new string with the given number of characters appended;
wchar_t *str_append(wchar_t *string, long long newelems, wchar_t value)
{
	const size_t oldlen = wcslen(string);
	const size_t newlen = oldlen + newelems;
	wchar_t *appended = (wchar_t *)malloc(sizeof(wchar_t) * (1 + newlen));
	wcscpy(appended, string);
	for (size_t i = oldlen; i < newlen; ++i)
		appended[i] = value;
	appended[newlen] = 0;
	return appended;
}

wchar_t *str_prepend(wchar_t *string, long long newelems, wchar_t value)
{
	const size_t newlen = wcslen(string) + newelems;
	wchar_t *appended = (wchar_t *)malloc(sizeof(wchar_t) * (1 + newlen));
	for (size_t i = 0; i < newelems; ++i)
		appended[i] = value;
	wcscpy(appended + newelems, string);
	appended[newlen] = 0;
	return appended;
}