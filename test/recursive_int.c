#include <stdio.h>

#include "../include/print.h"
#include "../include/recursive_int.h"

int main()
{
	// ^ test of: 'recursive_int_add' and 'recursive_int_add_i';

	recursive_int *r1 = alloc_recursive_int(154451, alloc_recursive_int(1070907, alloc_recursive_int(-69669, false)));
	recursive_int *r2 = alloc_recursive_int(-512134156, alloc_recursive_int(8060615135, alloc_recursive_int(15151, false)));

	recursive_int *r1_ = recursive_int_copy(r1);

	wchar_t *a1a = recursive_int_print_sum(r1, 10),
			*a1b = recursive_int_print_sum(r2, 10),
			*b1 = recursive_int_print_sum(r1_, 10);

	recursive_int *add = recursive_int_add(r1, r2);
	long long l = 9908051;
	recursive_int *addlong = recursive_int_add_i(r1_, l);

	wchar_t *o1a1 = recursive_int_print_sum(add, 10),
			*o1b1 = recursive_int_print_sum(addlong, 10);

	printf("Recursive int addition test 1 (in): %ls %ls\n", a1a, a1b);
	printf("Recursive int addition test 1 (out): %ls \n", o1a1);
	printf("Recursive int long long addition test 1 (in): %ls %lld\n", b1, l);
	printf("Recursive int long long addition test 1 (in): %ls \n\n", o1b1);

	free_recursive_int(add);
	free_recursive_int(addlong);

	free(a1a);
	free(a1b);
	free(b1);

	free(o1a1);
	free(o1b1);

	// ^ test of: recursive_int_mult;

	recursive_int *r3 = alloc_recursive_int(551351, alloc_recursive_int(1097090, false));
	recursive_int *r4 = alloc_recursive_int(-10443, false);

	wchar_t *c1a = recursive_int_print(r3, 10),
			*c1b = recursive_int_print(r4, 10);

	recursive_int *product = recursive_int_mult(r3, r4);
	wchar_t *o1c1 = recursive_int_print(product, 10);

	printf("Recursive int multiplication test 1 (in): %ls %ls\n", c1a, c1b);
	printf("Recursive int multiplication test 1 (out): %ls\n\n", o1c1);

	free(c1a);
	free(c1b);
	free(o1c1);

	free_recursive_int(product);
	free_recursive_int(r3);
	free_recursive_int(r4);

	// ^ test of: 'recursive_int_greater' and 'recursive_int_equal';

	recursive_int *r5 = alloc_recursive_int(9090801, alloc_recursive_int(1000900, alloc_recursive_int(790751, false)));
	recursive_int *r6 = alloc_recursive_int(90951, alloc_recursive_int(-1215, false));

	recursive_int *r5_ = recursive_int_copy(r5);

	wchar_t *d1a = recursive_int_print(r5, 10),
			*d1b = recursive_int_print(r6, 10),
			*e1b = recursive_int_print(r5_, 10);

	bool o1d1 = recursive_int_greater(r5, r6);
	bool o1e1 = recursive_int_equal(r5, r6),
		 o1e2 = recursive_int_equal(r5, r5_);

	printf("Recursive int greater test 1 (in): %ls %ls\n", d1a, d1b);
	printf("Recursive int greater test 1 (out): %d\n\n", o1d1);

	printf("Recursive int equal test 1 (in): %ls %ls\n", d1a, d1b);
	printf("Recursive int equal test 1 (out): %d\n", o1e1);
	printf("Recursive int equal test 2 (in): %ls %ls\n", d1a, e1b);
	printf("Recursive int equal test 2 (out): %d\n\n", o1e2);

	free(d1a);
	free(d1b);
	free(e1b);

	free_recursive_int(r5);
	free_recursive_int(r6);
	free_recursive_int(r5_);

	// ^ test of: recursive_int_llfit;
	recursive_int *r9 = alloc_recursive_int(4141513, false);
	recursive_int *r10 = alloc_recursive_int(15151, alloc_recursive_int(LLONG_MAX - 23, false));

	wchar_t *f1 = recursive_int_print(r9, 10),
			*f2 = recursive_int_print(r10, 10);

	bool o1f1 = recursive_int_llfit(r9),
		 o1f2 = recursive_int_llfit(r10);

	printf("Recursive int long long fit test 1 (in): %ls\n", f1);
	printf("Recursive int long long fit test 1 (out): %d\n", o1f1);
	printf("Recursive int long long fit test 2 (in): %ls\n", f2);
	printf("Recursive int long long fit test 2 (out): %d\n\n", o1f2);

	free_recursive_int(r10);

	free(f1);
	free(f2);
}