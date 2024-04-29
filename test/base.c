#include "../include/print.h"

// ! NOTE: the general shape for the tests is:
// 		1. check the function for the cases of some great depth;
// 		2. check the function for the cases of depth 1;
// 		3. check the function for the cases of 0;
// * This is PER A SINGLE ARGUMENT! So, the formula for the number of tests is:
// 		3 * argslen
// For testing, first finish another todo and implement a printing function;

int main()
{
	// ^ the test of: 'alloc_recursive_int' and 'free_recursive_int';

	recursive_int *r1 = alloc_recursive_int(3323909, false);
	recursive_int *r2 = alloc_recursive_int(-99943, alloc_recursive_int(1232009, alloc_recursive_int(-2323221, false)));
	wchar_t *a1 = recursive_int_print(r1, 10);
	wchar_t *a2 = recursive_int_print(r2, 10);
	wchar_t *o1a1 = recursive_int_print_sum(r1, 10);
	wchar_t *o1a2 = recursive_int_print_sum(r2, 10);

	printf("Recursive int allocation test 1 (in): %ls\n", a1);
	printf("Recursive int allocation test 1 (out): %ls\n", o1a1);
	printf("Recursive int allocation test 2 (in): %ls\n", a2);
	printf("Recursive int allocation test 2 (out): %ls\n\n", o1a2);

	free_recursive_int(r1);
	free_recursive_int(r2);
	free(a1);
	free(a2);
	free(o1a1);
	free(o1a2);

	// ^ the test of: 'recursive_int_copy';

	recursive_int *r3 = alloc_recursive_int(100090, alloc_recursive_int(-99097, alloc_recursive_int(779, false)));
	recursive_int *r4 = recrusive_int_copy(r3);
	r4->value++;
	r4->ri->value++;
	r4->ri->ri->value--;

	wchar_t *b1 = recursive_int_print(r3, 10);
	wchar_t *b2 = recursive_int_print(r4, 10);
	wchar_t *o1b1 = recursive_int_print_sum(r3, 10);
	wchar_t *o1b2 = recursive_int_print_sum(r4, 10);

	printf("Recursive int copying test 1 (in): %ls\n", b1);
	printf("Recursive int copying test 1 (out): %ls\n", o1b1);
	printf("Recursive int copying test 2 (in): %ls\n", b2);
	printf("Recursive int copying test 2 (out): %ls\n\n", o1b2);

	free_recursive_int(r3);
	free_recursive_int(r4);
	free(b1);
	free(b2);
	free(o1b1);
	free(o1b2);

	// ^ the test of: 'recursive_int_abs' and 'recursive_int_addinv';

	recursive_int *r5 = recursive_int_abs(alloc_recursive_int(1990, alloc_recursive_int(-89808, alloc_recursive_int(-4432, false))));
	recursive_int *r6 = recursive_int_addinv(alloc_recursive_int(-7390302, alloc_recursive_int(778350, alloc_recursive_int(-99987, false))));

	wchar_t *c1 = recursive_int_print(r5, 10);
	wchar_t *d1 = recursive_int_print(r6, 10);
	wchar_t *o1c1 = recursive_int_print_sum(r5, 10);
	wchar_t *o1d1 = recursive_int_print_sum(r6, 10);

	printf("Recursive int absolute value test 1 (in): %ls\n", c1);
	printf("Recursive int absolute value test 1 (out): %ls\n", o1c1);
	printf("Recursive int additive inverse test 1 (in): %ls\n", d1);
	printf("Recursive int additive inverse test 1 (out): %ls\n\n", o1d1);

	free_recursive_int(r5);
	free_recursive_int(r6);
	free(c1);
	free(d1);

	// ^ the test of: 'recursive_int_inc' and 'recursive_int_dec';
	recursive_int *r7 = alloc_recursive_int(LLONG_MAX, alloc_recursive_int(LLONG_MAX, false));
	recursive_int *r8 = alloc_recursive_int(LLONG_MIN, alloc_recursive_int(LLONG_MIN, false));
	recursive_int *r9 = alloc_recursive_int(999034, alloc_recursive_int(33243, false));
	recursive_int *r10 = alloc_recursive_int(-1123, alloc_recursive_int(-78903, false));

	wchar_t *e1 = recursive_int_print(r7, 10),
			*e2 = recursive_int_print(r9, 10),
			*f1 = recursive_int_print(r8, 10),
			*f2 = recursive_int_print(r10, 10);

	r7 = recursive_int_inc(r7);
	r9 = recursive_int_inc(r9);
	r8 = recursive_int_dec(r8);
	r10 = recursive_int_dec(r10);

	wchar_t *o1e1 = recursive_int_print(r7, 10),
			*o1e2 = recursive_int_print(r9, 10),
			*o1f1 = recursive_int_print(r8, 10),
			*o1f2 = recursive_int_print(r10, 10);

	printf("Recursive int increment test 1 (in): %ls\n", e1);
	printf("Recursive int increment test 1 (out): %ls\n", o1e1);
	printf("Recursive int increment test 2 (in): %ls\n", e2);
	printf("Recursive int increment test 2 (out): %ls\n", o1e2);

	printf("Recursive int decrement test 1 (in): %ls\n", f1);
	printf("Recursive int decrement test 1 (out): %ls\n", o1f1);
	printf("Recursive int decrement test 1 (in): %ls\n", f2);
	printf("Recursive int decrement test 1 (out): %ls\n\n", o1f2);

	free_recursive_int(r7);
	free_recursive_int(r8);
	free_recursive_int(r9);
	free_recursive_int(r10);

	free(e1);
	free(e2);
	free(f1);
	free(f2);

	free(o1e1);
	free(o1e2);
	free(o1f1);
	free(o1f2);

	// ^ the test of: 'recursive_zero()';

	recursive_int *zero = recursive_zero();
	recursive_int *g1 = recursive_int_print(zero, 10);
	recursive_int *o1g1 = recursive_int_print_sum(zero, 10);

	printf("Recursive zero test (in): %ls\n", g1);
	printf("Recursive zero test (out): %ls\n\n", o1g1);

	free_recursive_int(zero);
	free(g1);
	free(o1g1);

	// ^ the test of: 'get_negative' and 'get_positive';

	// ! ADD VALUES! 
	recursive_int *fposneg = alloc_recursive_int(0,
												 alloc_recursive_int(0,
																	 alloc_recursive_int(0,
																						 alloc_recursive_int(0,
																											 alloc_recursive_int(0,
																																 alloc_recursive_int(0,
																																					 alloc_recursive_int(0, false)))))));
	recursive_int *sposneg = alloc_recursive_int(0,
												 alloc_recursive_int(0,
																	 alloc_recursive_int(0,
																						 alloc_recursive_int(0,
																											 alloc_recursive_int(0,
																																 alloc_recursive_int(0,
																																					 alloc_recursive_int(0, false)))))));
	recursive_int *r11 = get_positive(fposneg);
	recursive_int *r12 = get_positive(sposneg);
	recursive_int *r13 = get_negative(fposneg);
	recursive_int *r13 = get_negative(sposneg);

	wchar_t *h1 = recursive_int_print_sum(fposneg, 10),
			*h2 = recursive_int_print_sum(sposneg, 10),
			*i1 = recursive_int_print_sum(fposneg, 10),
			*i2 = recursive_int_print_sum(sposneg, 10);

	wchar_t *o1h1 = recursive_int_print_sum(r11, 10),
			*o1h2 = recursive_int_print_sum(r12, 10),
			*o1i1 = recursive_int_print_sum(r13, 10),
			*o1i2 = recursive_int_print_sum(r13, 10);

	printf("Recursive int positive part test 1 (in): %ls\n", h1);
	printf("Recursive int positive part test 1 (out): %ls\n", o1h1);
	printf("Recursive int positive part test 2 (in): %ls\n", h2);
	printf("Recursive int positive part test 2 (out): %ls\n\n", o1h2);

	printf("Recursive int negative part test 1 (in): %ls\n", i1);
	printf("Recursive int negative part test 1 (out): %ls\n", o1i1);
	printf("Recursive int negative part test 2 (in): %ls\n", i2);
	printf("Recursive int negative part test 2 (out): %ls\n\n", o1i2);

	free_recursive_int(fposneg);
	free_recursive_int(sposneg);

	free_recursive_int(r11);
	free_recursive_int(r12);
	free_recursive_int(r13);
	free_recursive_int(r13);

	free(h1);
	free(h2);
	free(i1);
	free(i2);

	free(o1h1);
	free(o1h2);
	free(o1i1);
	free(o1i2);

	// ! the test of: 'first_not_full' and 'last_not_full';

	// ! the test of: 'recursive_int_last' and 'recursive_int_set_last';

	// ! the test of: 'recursive_int_depth';
	// ! the test of: 'recursive_int_revert';
}