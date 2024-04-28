#include "../include/print.h"

int main()
{
	// ^ test for: string_reverse;
	setlocale(LC_ALL, "C.UTF-8");
	wchar_t a1[30];
	wcscpy(a1, "This is a string. HubbaBubba!");

	wchar_t *oa1 = string_reverse(a1);
	printf("Reversed test 1 (in):%ls \n", a1);
	printf("Reversed test 1 (out):%ls \n\n", oa1);
	free(oa1);

	wchar_t a2[2];
	wcscpy(a2, "-");
	wchar_t *oa2 = string_reverse(a2);
	printf("Reversed test 2 (in):%ls \n", a2);
	printf("Reversed test 2 (out):%ls \n\n", oa2);
	free(oa2);

	// ^ test for: base_representation;
	long long b1 = 4443090;
	long long b2 = -902;
	long long o1b1 = base_representation(b1, 8),
			  o2b1 = base_representation(b1, 2),
			  o3b1 = base_representation(b1, 10),
			  o4b1 = base_representation(b1, 1219);
	long long o1b2 = base_representation(b2, 2),
			  o2b2 = base_representation(b2, 115);

	printf("Base representation test 1 (in):%ls \n", b1);
	printf("Base representation test 1 (out, 1):%ls \n", o1b1);
	printf("Base representation test 1 (out, 2):%ls \n", o2b1);
	printf("Base representation test 1 (out, 3):%ls \n", o3b1);
	printf("Base representation test 1 (out, 4):%ls \n\n", o4b1);

	printf("Base representation test 2 (in):%ls \n", b2);
	printf("Base representation test 2 (out, 1):%ls \n", o2b1);
	printf("Base representation test 2 (out, 2):%ls \n\n", o2b2);

	free(o1b1);
	free(o2b1);
	free(o3b1);
	free(o4b1);
	free(o1b2);
	free(o2b2);

	// ^ test for: symbolic_bit_add;
	wchar_t c1a[4], c1b[4];

	strcpy(c1a, (wchar_t *)"001");
	strcpy(c1b, (wchar_t *)"011");
	wchar_t *o1c1 = symbolic_bit_add(c1a, c1b, 0, 2);

	strcpy(c1a, (wchar_t *)"001");
	strcpy(c1b, (wchar_t *)"011");
	wchar_t *o2c1 = symbolic_bit_add(c1a, c1b, 1, 9);

	printf("Symbolic bit addition test 1 (in): %ls %ls\n", c1a, c1b);
	printf("Symbolic bit addition test 1 (out, 1):%ls \n", o1c1);
	printf("Symbolic bit addition test 1 (out, 2):%ls \n\n", o2c1);

	free(o1c1);
	free(o2c1);

	// ^ test for: symbolic_bit_sub;
	strcpy(c1a, (wchar_t *)"001");
	strcpy(c1b, (wchar_t *)"011");

	wchar_t *o1d1 = symbolic_bit_sub(c1b, c1a, 0, 2);

	printf("Symbolic bit subtraction test 1 (in): %ls %ls\n", c1a, c1b);
	printf("Symbolic bit subtraction test 1 (out):%ls \n\n", o1d1);

	free(o1d1);

	// ^ tests for: symbolic_addition;
	strcpy(c1a, (wchar_t *)"001");
	strcpy(c1b, (wchar_t *)"011");

	wchar_t e2a[7];
	strcpy(e2a, (wchar_t *)"997824");
	wchar_t e2b[6];
	strcpy(e2b, (wchar_t *)"aaAk3");

	wchar_t e3a[5];
	strcpy(e3a, (wchar_t *)"1920");
	wchar_t e3b[4];
	strcpy(e3a, (wchar_t *)"-10");

	wchar_t *o1e1 = symbolic_addition(c1a, c1b, 2),
			*o1e2 = symbolic_addition(e2a, e2b, 200),
			*o1e3 = symbolic_addition(e3a, e3b, 10);

	printf("Symbolic addition test 1 (in): %ls %ls\n", c1a, c1b);
	printf("Symbolic addition test 1 (out, 1):%ls \n\n", o1e1);

	printf("Symbolic addition test 2 (in): %ls %ls\n", e2a, e2b);
	printf("Symbolic addition test 2 (out, 1):%ls \n\n", o1e2);

	printf("Symbolic addition test 3 (in): %ls %ls\n", e3a, e3b);
	printf("Symbolic addition test 3 (out, 1):%ls \n\n", o1e3);

	// ^ tests for: symbolic_subtraction; 

	wchar_t f1a[4]; 
	wchar_t f1b[3]; 

	strcpy(f1a, "993"); 	
	strcpy(f1b, "4s"); 

	wchar_t *o1f1 = symbolic_subtraction(f1a, f1b, 200); 

	printf("Symbolic subtraction test 1 (in): %ls %ls\n", f1a, f1b);
	printf("Symbolic subtraction test 1 (out, 1):%ls \n\n", o1f1);

	free(o1f1); 

	// ! test for: symbolic_plus;

	// ! test for: recursive_int_print;
	// ! test for: recursive_int_print_sum;
}