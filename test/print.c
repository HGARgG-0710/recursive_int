#include <stdio.h>
#include "../include/print.h"

int main()
{
	// ^ test for: string_reverse;
	setlocale(LC_ALL, ".utf8");

	wchar_t *a1 = (wchar_t *)malloc(30 * sizeof(wchar_t));
	wcscpy(a1, (wchar_t *)L"This is a string. HubbaBubba!");

	wchar_t *oa1 = string_reverse(a1);

	printf("Reversed test 1 (in): %ls \n", a1);
	printf("Reversed test 1 (out): %ls \n\n", oa1);

	free(a1);
	free(oa1);

	wchar_t *a2 = (wchar_t *)malloc(sizeof(wchar_t) * 2);
	wcscpy(a2, (wchar_t *)L"-");

	wchar_t *oa2 = string_reverse(a2);
	printf("Reversed test 2 (in): %ls \n", a2);
	printf("Reversed test 2 (out): %ls \n\n", oa2);

	free(a2);
	free(oa2);

	// ^ test for: base_representation;
	long long b1 = 4443090;
	long long b2 = -902;
	wchar_t *o1b1 = base_representation(b1, 8),
			*o2b1 = base_representation(b1, 2),
			*o3b1 = base_representation(b1, 10),
			*o4b1 = base_representation(b1, 1219);
	wchar_t *o1b2 = base_representation(b2, 2),
			*o2b2 = base_representation(b2, 115);

	printf("Base representation test 1 (in): %lld \n", b1);
	printf("Base representation test 1 (out, 1): %ls \n", o1b1);
	printf("Base representation test 1 (out, 2): %ls \n", o2b1);
	printf("Base representation test 1 (out, 3): %ls \n", o3b1);
	// ! same as below... - create proper alphabets instead of this...
	// printf("Base representation test 1 (out, 4): %ls \n\n", o4b1);

	printf("Base representation test 2 (in): %lld \n", b2);
	printf("Base representation test 2 (out): %ls \n", o1b2);
	// % This right here is a fantastic example of why using UTF8 to represent number bases is a BAD idea.
	// TODO: in future versions of the library, replace with proper alphabets API...;
	// printf("Base representation test 2 (out, 2): %ls \n\n", o2b2);

	free(o1b1);
	free(o2b1);
	free(o3b1);
	free(o4b1);
	free(o1b2);
	free(o2b2);

	// ^ test for: symbolic_left_shift

	wchar_t x[10] = L"Siebgrau!";

	printf("Symbolic shift left test 1 (in): %ls\n", x);
	printf("Symbolic shift left test 1 (out): %ls\n", symbolic_left_shift(x));
	printf("Symbolic shift left test 2 (in): %ls\n", x);
	printf("Symbolic shift left test 2 (out): %ls\n", symbolic_left_shift(x));
	printf("Symbolic shift left test 3 (in): %ls\n", x);
	printf("Symbolic shift left test 3 (out): %ls\n\n", symbolic_left_shift(x));

	// ^ test for: symbolic_bit_add;
	wchar_t *c1a = (wchar_t *)malloc(4 * sizeof(wchar_t)),
			*c1b = (wchar_t *)malloc(4 * sizeof(wchar_t));
	wcscpy(c1a, (wchar_t *)L"008");
	wcscpy(c1b, (wchar_t *)L"013");

	printf("Symbolic bit addition test 1 (in): %ls %ls\n", c1a, c1b);
	printf("Symbolic bit addition test 1 (out): %ls \n", c1a = symbolic_bit_add(c1a, c1b, 0, 9));

	wcscpy(c1a, (wchar_t *)L"101");
	wcscpy(c1b, (wchar_t *)L"111");

	printf("Symbolic bit addition test 2 (in): %ls %ls \n", c1a, c1b);
	c1a = symbolic_bit_add(c1a, c1b, 2, 2);
	printf("Symbolic bit addition test 2 (out): %ls \n\n", c1a);

	// ^ test for: symbolic_bit_sub;
	wcscpy(c1a, (wchar_t *)L"0001");
	wcscpy(c1b, (wchar_t *)L"011");

	printf("Symbolic bit subtraction test 1 (in): %ls %ls\n", c1a, c1b);
	printf("Symbolic bit subtraction test 1 (out): %ls \n\n", c1b = symbolic_bit_sub(c1b, c1a, 0, 2));

	// ^ tests for: symbolic_addition;
	wcscpy(c1a, (wchar_t *)L"0001");
	wcscpy(c1b, (wchar_t *)L"011");

	wchar_t *e2a = (wchar_t *)malloc(7 * sizeof(wchar_t));
	wcscpy(e2a, (wchar_t *)L"997824");
	wchar_t *e2b = (wchar_t *)malloc(6 * sizeof(wchar_t));
	wcscpy(e2b, (wchar_t *)L"aaAk3");

	wchar_t *e3a = (wchar_t *)malloc(5 * sizeof(wchar_t));
	wcscpy(e3a, (wchar_t *)L"1920");
	wchar_t *e3b = (wchar_t *)malloc(4 * sizeof(wchar_t));
	wcscpy(e3b, (wchar_t *)L"-10");

	printf("Symbolic addition test 1 (in): %ls %ls\n", c1a, c1b);
	printf("Symbolic addition test 1 (out): %ls \n\n", c1a = symbolic_addition(c1a, c1b, 2));

	printf("Symbolic addition test 2 (in): %ls %ls\n", e2a, e2b);
	printf("Symbolic addition test 2 (out): %ls \n\n", e2a = symbolic_addition(e2a, e2b, 200));

	printf("Symbolic addition test 3 (in): %ls %ls\n", e3a, e3b);
	printf("Symbolic addition test 3 (out): %ls \n\n", e3a = symbolic_addition(e3a, e3b, 10));

	free(e2a);
	free(e2b);
	free(e3a);
	free(e3b);
	free(c1a);
	free(c1b);

	// ^ tests for: symbolic_subtraction;

	wchar_t *f1a = (wchar_t *)malloc(4 * sizeof(wchar_t));
	wchar_t *f1b = (wchar_t *)malloc(3 * sizeof(wchar_t));

	wcscpy(f1a, (wchar_t *)L"993");
	wcscpy(f1b, (wchar_t *)L"4s");

	printf("Symbolic subtraction test 1 (in): %ls %ls\n", f1a, f1b);
	printf("Symbolic subtraction test 1 (out, 1): %ls \n\n", f1a = symbolic_subtraction(f1a, f1b, 200));

	free(f1a);
	free(f1b);

	// ^ tests for: symbolic_plus;

	wchar_t *g1a = (wchar_t *)malloc(7 * sizeof(wchar_t));
	wchar_t *g1b = (wchar_t *)malloc(4 * sizeof(wchar_t));

	wcscpy(g1a, (wchar_t *)L"231203");
	wcscpy(g1b, (wchar_t *)L"112");

	wchar_t *o1g1 = symbolic_plus(g1a, g1b);

	wchar_t *g2a = (wchar_t *)malloc(8 * sizeof(wchar_t));
	wchar_t *g2b = (wchar_t *)malloc(7 * sizeof(wchar_t));

	wcscpy(g2a, (wchar_t *)L"-abc204");
	wcscpy(g2b, (wchar_t *)L"-20943");

	wchar_t *o1g2 = symbolic_plus(g2a, g2b);

	printf("Symbolic sum test 1 (in): %ls %ls\n", g1a, g1b);
	printf("Symbolic sum test 1 (out): %ls \n\n", o1g1);

	printf("Symbolic sum test 2 (in): %ls %ls\n", g2a, g2b);
	printf("Symbolic sum test 2 (out): %ls \n\n", o1g2);

	free(o1g1);
	free(o1g2);

	// ^ tests for: recursive_int_print;

	recursive_int subh33 = {
		.value = -292292,
		.ri = false};

	recursive_int subh32 = {
		.value = -741234,
		.ri = &subh33};

	recursive_int subh31 = {
		.value = 88043,
		.ri = &subh32};

	recursive_int h1 = {.value = 7901907, .ri = false};
	recursive_int h2 = {.value = 0, .ri = false};
	recursive_int h3 = {.value = 20098,
						.ri = &subh31};

	wchar_t *o1h1 = recursive_int_print(&h1, 2),
			*o2h1 = recursive_int_print(&h1, 10),
			*o3h1 = recursive_int_print(&h1, 20);

	printf("Printing (a recursive_int) test 1 (out, 1): %ls \n", o1h1);
	printf("Printing (a recursive_int) test 1 (out, 2): %ls \n", o2h1);
	printf("Printing (a recursive_int) test 1 (out, 3): %ls \n\n", o3h1);

	wchar_t *o1h2 = recursive_int_print(&h2, 5),
			*o2h2 = recursive_int_print(&h2, 18),
			*o3h2 = recursive_int_print(&h2, 28);

	printf("Printing (a recursive_int) test 2 (out, 1): %ls \n", o1h2);
	printf("Printing (a recursive_int) test 2 (out, 2): %ls \n", o2h2);
	printf("Printing (a recursive_int) test 2 (out, 3): %ls \n\n", o3h2);

	wchar_t *o1h3 = recursive_int_print(&h3, 10),
			*o2h3 = recursive_int_print(&h3, 20),
			*o3h3 = recursive_int_print(&h3, 11);

	printf("Printing (a recursive_int) test 3 (out, 1): %ls \n", o1h3);
	printf("Printing (a recursive_int) test 3 (out, 2): %ls \n", o2h3);
	printf("Printing (a recursive_int) test 3 (out, 3): %ls \n\n", o3h3);

	free(o1h1);
	free(o2h1);
	free(o3h1);

	free(o1h2);
	free(o2h2);
	free(o3h2);

	free(o1h3);
	free(o2h3);
	free(o3h3);

	// ^ recursive_int_print_sum test;
	wchar_t *o1i1 = recursive_int_print_sum(&h1, 2),
			*o2i1 = recursive_int_print_sum(&h1, 10),
			*o3i1 = recursive_int_print_sum(&h1, 200);

	wchar_t *o1i2 = recursive_int_print_sum(&h2, 5),
			*o2i2 = recursive_int_print_sum(&h2, 18),
			*o3i2 = recursive_int_print_sum(&h2, 48);

	wchar_t *o1i3 = recursive_int_print_sum(&h3, 10),
			*o2i3 = recursive_int_print_sum(&h3, 20),
			*o3i3 = recursive_int_print_sum(&h3, 120);

	printf("Printing sum test 1 (out, 1):%ls \n", o1i1);
	printf("Printing sum test 1 (out, 2):%ls \n", o2i1);
	printf("Printing sum test 1 (out, 3):%ls \n\n", o3i1);

	printf("Printing sum test 2 (out, 1):%ls \n", o1i2);
	printf("Printing sum test 2 (out, 2):%ls \n", o2i2);
	printf("Printing sum test 2 (out, 3):%ls \n\n", o3i2);

	printf("Printing sum test 3 (out, 1):%ls \n", o1i3);
	printf("Printing sum test 3 (out, 2):%ls \n", o2i3);
	printf("Printing sum test 3 (out, 3):%ls \n\n", o3i3);

	free(o1i1);
	free(o2i1);
	free(o3i1);

	free(o1i2);
	free(o2i2);
	free(o3i2);

	free(o1i3);
	free(o2i3);
	free(o3i3);
}