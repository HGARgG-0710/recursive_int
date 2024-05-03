// TODO: refactor the tests... (some of it can be generalized, at least...);

#include "../include/print.h"
#include "../include/optimized.h"

int main()
{
	// ^ test of: de_zero;

	recursive_int *r1 = alloc_recursive_int(0, alloc_recursive_int(0, alloc_recursive_int(45999354, alloc_recursive_int(-7732, alloc_recursive_int(0, alloc_recursive_int(5151546, alloc_recursive_int(0, alloc_recursive_int(661464, false))))))));
	wchar_t *dezin = recursive_int_print_sum(r1, 10);
	printf("Recursive int de-zero test 1 (in): %ls\n", dezin);

	recursive_int *dez = de_zero(r1);
	wchar_t *dezout = recursive_int_print_sum(dez, 10);
	printf("Recursive int de-zero test 1 (out): %ls\n\n", dezout);

	free_recursive_int(dez);

	free(dezin);
	free(dezout);

	// ^ test of: recursive_int_minimize;

	recursive_int *r2 = alloc_recursive_int(-7709997779999999999, alloc_recursive_int(-7897854016086543794, alloc_recursive_int(LLONG_MIN + 4, alloc_recursive_int(LLONG_MIN + 1000, false))));
	wchar_t *a1 = recursive_int_print_sum(r2, 10);
	printf("Recursive int minimization test 1 (in): %ls\n", a1);

	recursive_int *minimized1 = recursive_int_minimize(r2);
	wchar_t *o1a1 = recursive_int_print_sum(minimized1, 10);
	printf("Recursive int minimization test 1 (out): %ls\n", o1a1);

	recursive_int *r3 = alloc_recursive_int(2342241343532367543, alloc_recursive_int(7764556617070970965, alloc_recursive_int(LLONG_MAX - 32, alloc_recursive_int(LLONG_MAX - 535343, false))));
	wchar_t *a2 = recursive_int_print_sum(r3, 10);
	printf("Recursive int minimization test 2 (in): %ls\n", a2);

	recursive_int *minimized2 = recursive_int_minimize(r3);
	wchar_t *o1a2 = recursive_int_print_sum(minimized2, 10);
	printf("Recursive int minimization test 2 (out): %ls\n\n", o1a2);

	free_recursive_int(r2);
	free_recursive_int(r3);

	free(a1);
	free(a2);
	free(o1a1);
	free(o1a2);

	// ^ test of: recursive_int_diff and  recursive_int_sum;

	recursive_int *r4 = alloc_recursive_int(55351, alloc_recursive_int(554151, false));
	recursive_int *r5 = alloc_recursive_int(-33213415, alloc_recursive_int(-661559, alloc_recursive_int(-673643, false)));

	recursive_int *r6 = alloc_recursive_int(8879601, alloc_recursive_int(1412431, alloc_recursive_int(56106510, false)));
	recursive_int *r7 = alloc_recursive_int(-34341406, alloc_recursive_int(-65196591, alloc_recursive_int(-441959, false)));

	recursive_int *r4_ = recursive_int_copy(r4),
				  *r5_ = recursive_int_copy(r5),
				  *r6_ = recursive_int_copy(r6),
				  *r7_ = recursive_int_copy(r7);

	wchar_t *b1a = recursive_int_print(r4, 10),
			*b1b = recursive_int_print(r5, 10),
			*b2a = recursive_int_print(r4, 10),
			*b2b = recursive_int_print(r6, 10),
			*b3a = recursive_int_print(r5, 10),
			*b3b = recursive_int_print(r7, 10),
			*c1a = recursive_int_print(r4, 10),
			*c1b = recursive_int_print(r5, 10),
			*c2a = recursive_int_print(r4, 10),
			*c2b = recursive_int_print(r6, 10),
			*c3a = recursive_int_print(r5, 10),
			*c3b = recursive_int_print(r7, 10);

	recursive_int *rsum1 = recursive_int_sum(r4, r5);

	r4 = recursive_int_copy(r4_);
	r5 = recursive_int_copy(r5_);

	recursive_int *rsum2 = recursive_int_sum(r4, r6);

	r4 = recursive_int_copy(r4_);
	r6 = recursive_int_copy(r6_);

	recursive_int *rsum3 = recursive_int_sum(r5, r7);

	r5 = recursive_int_copy(r5_);
	r7 = recursive_int_copy(r7_);

	recursive_int *rdiff1 = recursive_int_diff(r4, r5);

	r4 = recursive_int_copy(r4_);
	r5 = recursive_int_copy(r5_);

	recursive_int *rdiff2 = recursive_int_diff(r4, r6);

	r4 = recursive_int_copy(r4_);
	r6 = recursive_int_copy(r6_);

	recursive_int *rdiff3 = recursive_int_diff(r5, r7);

	r5 = recursive_int_copy(r5_);
	r7 = recursive_int_copy(r7_);

	wchar_t *o1b1 = recursive_int_print(rsum1, 10),
			*o1b2 = recursive_int_print(rsum2, 10),
			*o1b3 = recursive_int_print(rsum3, 10),
			*o1c1 = recursive_int_print(rdiff1, 10),
			*o1c2 = recursive_int_print(rdiff2, 10),
			*o1c3 = recursive_int_print(rdiff3, 10);

	printf("Recursive int sum test 1 (in): %ls %ls\n", b1a, b1b);
	printf("Recursive int sum test 1 (out): %ls\n", o1b1);
	printf("Recursive int sum test 2 (in): %ls %ls\n", b2a, b2b);
	printf("Recursive int sum test 2 (out): %ls\n", o1b2);
	printf("Recursive int sum test 3 (in): %ls %ls\n", b3a, b3b);
	printf("Recursive int sum test 3 (out): %ls\n\n", o1b3);

	printf("Recursive int difference test 1 (in): %ls %ls\n", c1a, c1b);
	printf("Recursive int difference test 1 (out): %ls\n", o1c1);
	printf("Recursive int difference test 2 (in): %ls %ls\n", c2a, c2b);
	printf("Recursive int difference test 2 (out): %ls\n", o1c2);
	printf("Recursive int difference test 3 (in): %ls %ls\n", c3a, c3b);
	printf("Recursive int difference test 3 (out): %ls\n\n", o1c3);

	free(b1a);
	free(b1b);
	free(b2a);
	free(b2b);
	free(b3a);
	free(b3b);

	free(o1b1);
	free(o1b2);
	free(o1b3);

	free(c1a);
	free(c1b);
	free(c2a);
	free(c2b);
	free(c3a);
	free(c3b);

	free(o1c1);
	free(o1c2);
	free(o1c3);

	free_recursive_int(r4);
	free_recursive_int(r5);
	free_recursive_int(r6);
	free_recursive_int(r7);

	free_recursive_int(r4_);
	free_recursive_int(r5_);
	free_recursive_int(r6_);
	free_recursive_int(r7_);

	// ^ recursive_int_optimized_revert;

	recursive_int *r8 = alloc_recursive_int(6613150, alloc_recursive_int(1061038, alloc_recursive_int(551, alloc_recursive_int(-7, false))));
	wchar_t *d1 = recursive_int_print_sum(r8, 10);
	recursive_int *x = recursive_int_optimized_revert(r8);
	wchar_t *o1d1 = recursive_int_print_sum(x, 10);

	printf("Recursive int optimized revert test (in): %ls\n", d1);
	printf("Recursive int optimized revert test (out): %ls\n\n", o1d1);

	free_recursive_int(x);

	free(d1);
	free(o1d1);

	// ^ test of: recursive_int_optimize;

	recursive_int *r9 = alloc_recursive_int(1340193740, alloc_recursive_int(-51510561058164019, alloc_recursive_int(-4134105610639, alloc_recursive_int(LLONG_MAX - 51561, alloc_recursive_int(LLONG_MAX - 5514, alloc_recursive_int(0, alloc_recursive_int(677, false)))))));
	recursive_int *r10 = alloc_recursive_int(-7651561, alloc_recursive_int(5105015801593410346, alloc_recursive_int(51056106518969869, alloc_recursive_int(LLONG_MIN + 1112341, alloc_recursive_int(0, alloc_recursive_int(LLONG_MIN + 11515, alloc_recursive_int(677, false)))))));

	recursive_int *opr9 = recursive_int_optimize(r9),
				  *opr10 = recursive_int_optimize(r10);

	wchar_t *e1 = recursive_int_print_sum(r9, 10),
			*e2 = recursive_int_print_sum(r10, 10),
			*o1e1 = recursive_int_print_sum(opr9, 10),
			*o1e2 = recursive_int_print_sum(opr10, 10);

	printf("Recursive int optimize test 1 (in): %ls\n", e1);
	printf("Recursive int optimize test 1 (out): %ls\n", o1e1);
	printf("Recursive int optimize test 2 (in): %ls\n", e2);
	printf("Recursive int optimize test 2 (out): %ls\n\n", o1e2);

	free_recursive_int(r9);
	free_recursive_int(r10);
	free_recursive_int(opr9);
	free_recursive_int(opr10);

	free(e1);
	free(e2);
	free(o1e1);
	free(o1e2);

	// ^ test of: recursive_int_equal_optimized;

	recursive_int *r11 = alloc_recursive_int(LLONG_MIN + 77151, alloc_recursive_int(LLONG_MIN + 15151343, alloc_recursive_int(LLONG_MIN + 141890, alloc_recursive_int(-3413, false))));
	recursive_int *r12 = recursive_int_copy(r11);
	recursive_int *r13 = alloc_recursive_int(77151, alloc_recursive_int(5151342, alloc_recursive_int(LLONG_MAX - 66086, false)));

	recursive_int *opr11 = recursive_int_optimize(r11);
	recursive_int *opr12 = recursive_int_optimize(r12);
	recursive_int *opr13 = recursive_int_optimize(r13);

	wchar_t *f1a = recursive_int_print_sum(opr11, 10),
			*f1b = recursive_int_print_sum(opr12, 10),
			*f2a = recursive_int_print_sum(opr11, 10),
			*f2b = recursive_int_print_sum(opr13, 10);

	const bool o1f1 = recursive_int_equal_optimized(opr11, opr12);
	const bool o1f2 = recursive_int_equal_optimized(opr11, opr13);

	printf("Recursive int equal test (in): %ls %ls\n", f1a, f1b);
	printf("Recursive int equal test (out): %d\n", o1f1);
	printf("Recursive int equal test (in): %ls %ls\n", f2a, f2b);
	printf("Recursive int equal test (out): %d\n", o1f2);

	free_recursive_int(r11);
	free_recursive_int(r12);
	free_recursive_int(r13);

	free_recursive_int(opr11);
	free_recursive_int(opr12);
	free_recursive_int(opr13);

	free(f1a);
	free(f1b);
	free(f2a);
	free(f2b);
}