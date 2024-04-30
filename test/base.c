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

	// ^ the test of: 'recursive_zero';

	recursive_int *zero = recursive_zero();
	recursive_int *g1 = recursive_int_print(zero, 10);
	recursive_int *o1g1 = recursive_int_print_sum(zero, 10);

	printf("Recursive zero test (in): %ls\n", g1);
	printf("Recursive zero test (out): %ls\n\n", o1g1);

	free_recursive_int(zero);
	free(g1);
	free(o1g1);

	// ^ the test of 'recursive_int_from_ll'; 

	long long testval = 1051513; 
	recursive_int * fromll = recursive_int_from_ll(testval); 
	wchar_t * out = recursive_int_print(fromll, 10);
	
	printf("Recursive int from-long-long conversion test 1 (in): %lld\n", testval); 	
	printf("Recursive int from-long-long conversion test 1 (out): %ls\n", out); 

	free(out); 
	free_recursive_int(fromll); 

	// ^ the test of: 'get_negative' and 'get_positive';

	recursive_int *fposneg = alloc_recursive_int(-1343290,
												 alloc_recursive_int(-99908,
																	 alloc_recursive_int(3421436,
																						 alloc_recursive_int(5544532,
																											 alloc_recursive_int(-343090,
																																 alloc_recursive_int(-77860,
																																					 alloc_recursive_int(65514, false)))))));
	recursive_int *sposneg = alloc_recursive_int(-9617,
												 alloc_recursive_int(7513,
																	 alloc_recursive_int(5414,
																						 alloc_recursive_int(90651,
																											 alloc_recursive_int(6369,
																																 alloc_recursive_int(0,
																																					 alloc_recursive_int(0, false)))))));
	recursive_int *r11 = get_positive(fposneg);
	recursive_int *r12 = get_positive(sposneg);
	recursive_int *r13 = get_negative(fposneg);
	recursive_int *r14 = get_negative(sposneg);

	wchar_t *h1 = recursive_int_print_sum(fposneg, 10),
			*h2 = recursive_int_print_sum(sposneg, 10),
			*i1 = recursive_int_print_sum(fposneg, 10),
			*i2 = recursive_int_print_sum(sposneg, 10);

	wchar_t *o1h1 = recursive_int_print_sum(r11, 10),
			*o1h2 = recursive_int_print_sum(r12, 10),
			*o1i1 = recursive_int_print_sum(r13, 10),
			*o1i2 = recursive_int_print_sum(r14, 10);

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
	free_recursive_int(r14);

	free(h1);
	free(h2);
	free(i1);
	free(i2);

	free(o1h1);
	free(o1h2);
	free(o1i1);
	free(o1i2);

	// ^ the test of: 'first_not_full' and 'last_not_full';

	recursive_int *r15 = alloc_recursive_int(LLONG_MAX, alloc_recursive_int(LLONG_MIN, alloc_recursive_int(170900, alloc_recursive_int(LLONG_MAX, alloc_recursive_int(LLONG_MAX, alloc_recursive_int(77790, false))))));
	recursive_int *r16 = alloc_recursive_int(LLONG_MIN, false);

	recursive_int *fnf1 = first_not_full(r15);
	recursive_int *lnf1 = last_not_full(r15);
	recursive_int *fnf2 = first_not_full(r16);
	recursive_int *lnf2 = last_not_full(r16);

	wchar_t *j1 = recursive_int_print_sum(r15, 10);
	wchar_t *j2 = recursive_int_print_sum(r15, 10);
	wchar_t *k1 = recursive_int_print_sum(r16, 10);
	wchar_t *k2 = recursive_int_print_sum(r16, 10);

	wchar_t *o1j1 = recursive_int_print_sum(fnf1, 10);
	wchar_t *o1j2 = recursive_int_print_sum(fnf2, 10);
	wchar_t *o1k1 = recursive_int_print_sum(lnf1, 10);
	wchar_t *o1k2 = recursive_int_print_sum(lnf2, 10);

	printf("Recursive int first not full test 1 (in): %ls\n", j1);
	printf("Recursive int first not full test 1 (out): %ls\n", o1j1);
	printf("Recursive int first not full test 2 (in): %ls\n", j2);
	printf("Recursive int first not full test 2 (out): %ls\n\n", o1j2);

	printf("Recursive int last not full test 1 (in): %ls\n", k1);
	printf("Recursive int last not full test 1 (out): %ls\n", o1k1);
	printf("Recursive int last not full test 2 (in): %ls\n", k2);
	printf("Recursive int last not full test 2 (out): %ls\n\n", o1k2);

	free_recursive_int(r15);
	free_recursive_int(r16);

	free_recursive_int(fnf1);
	free_recursive_int(lnf1);
	free_recursive_int(fnf2);
	free_recursive_int(lnf2);

	free(j1);
	free(j2);
	free(k1);
	free(k2);

	// ^ the test of: 'recursive_int_last' and 'recursive_int_set_last';

	recursive_int *r17 = alloc_recursive_int(10980, alloc_recursive_int(29807, alloc_recursive_int(-4431, false)));
	wchar_t *l1 = recursive_int_print_sum(r17, 10);

	recursive_int *last = recursive_int_last(r17);
	recursive_int *r18 = alloc_recursive_int(99374, alloc_recursive_int(-7743, alloc_recursive_int(0, false)));
	recursive_int_set_last(r17, r18);
	wchar_t *m1 = recursive_int_print_sum(r17, 10);

	recursive_int *newlast = recursive_int_last(r17);

	wchar_t *o1l1 = recursive_int_print_sum(last, 10),
			*o1m1 = recursive_int_print_sum(newlast, 10);

	printf("Recursive int last node test 1 (in): %ls\n", l1);
	printf("Recursive int last node test 1 (out): %ls\n\n", o1l1);

	printf("Recursive int set last node test 1 (in): %ls\n", m1);
	printf("Recursive int set last node test 1 (out): %ls\n\n", o1m1);

	free_recursive_int(r17);
	free_recursive_int(r18);
	free_recursive_int(last);

	free(l1);
	free(m1);
	free(o1l1);
	free(o1m1);

	// ^ the test of: 'recursive_int_depth';
	recursive_int *r19 = alloc_recursive_int(343109, alloc_recursive_int(-78623, alloc_recursive_int(79866, alloc_recursive_int(445698, false))));
	recursive_int *r20 = recurisve_zero();

	recursive_int *depth1 = recursive_int_depth(r19),
				  *depth2 = recursive_int_depth(r20);

	wchar_t *n1 = recursive_int_print_sum(r19, 10),
			*n2 = recursive_int_print_sum(r20, 10);
	wchar_t *o1n1 = recursive_int_print_sum(depth1, 10),
			*o1n2 = recursive_int_print_sum(depth2, 10);

	printf("Recursive int depth test 1 (in): %ls\n", n1);
	printf("Recursive int depth test 1 (out): %ls\n", o1n1);
	printf("Recursive int depth test 2 (in): %ls\n", n2);
	printf("Recursive int depth test 2 (out): %ls\n\n", o1n2);

	free_recursive_int(r19);
	free_recursive_int(r20);
	free_recursive_int(depth1);
	free_recursive_int(depth2);

	free(n1);
	free(n2);
	free(o1n1);
	free(o1n2);

	// ^ the test of: 'recursive_int_revert';
	recursive_int *r21 = alloc_recursive_int(43320, alloc_recursive_int(-99651, alloc_recursive_int(-51060, alloc_recursive_int(77448, false))));
	wchar_t *o1 = recursive_int_print_sum(r21, 10);

	recursive_int *reverted = recursive_int_revert(r21);
	wchar_t *o1o1 = recursive_int_print_sum(reverted, 10);

	printf("Recursive int revert test 1 (in): %ls, \n", o1);
	printf("Recursive int revert test 1 (out): %ls, \n", o1o1);

	free_recursive_int(r21);

	free(o1);
	free(o1o1);
}