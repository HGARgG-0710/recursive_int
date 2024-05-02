<!-- TODO: be more specific - what are the return values AND whether they are optimized or not. -->
<!-- TODO: VITAL - write that the library (in general) assumes that the dynamic allocation is used; -->
<!-- ! Fix that - make sure that static allocation + pointers equally viable; -->

# recursive_int

This is a small C library that wholy implements Integers via recursion.
There is no inherent max possible size of the integers allocatable with it,
only limitations are due to the user's RAM.

NOTE: in the future, the library's orientation may change drastically (as a result of expansion).

temp note: library's still not recommended for use, as there is presently a great space for optimization.
Also - some of the methods could use a bit of re-doing (particularly true of the `print` module).

## Documentation

### Definition

The "recursive integers" are basically linked lists, representing their sums.
From this definition various properties sprout and the library contains the methods
needed to acommodate some of them, as well as mirroring various basic arithmetic interfaces
on integers.

### Headers

1. `base.h` - contains basic operations on the recursive_int structure (also the structure itself);
2. `optimized.h` - most of operations in `base.h` are on "unoptimized" integers (those that can contain sign alterations and zeros); Contains operations related to optimizing them (saves memory, takes additional time to do, but make writing algorithms a lot easier).
3. `recursive_int.h` - methods that depend upon `optimized.h`, but don't relate to optimization itself.
4. `print.h` - methods for printing the recursive integers, either as a sum or as a precise value in a given base;

#### `base.h`

##### Definitions

```c
typedef struct
{
	recursive_int *ri;
	long long value;
} recursive_int;
```

##### Methods

```c
recursive_int *alloc_recursive_int(long long value, recursive_int * ri)
```

Dynamically alocates a new `recursive_int` and returns a pointer to it. Note that only one new layer is allocated.

&nbsp;

```c
recursive_int *free_recursive_int(recursive_int *)
```

Frees the `recursive_int` using the given pointer to it (note: THE ALLOCATION PROCEDURE IS RECURSIVE).

&nbsp;

```c
recursive_int *recursive_int_copy(recursive_int *)
```

Dynamically allocates a new copy of a given recursive_int.

&nbsp;

```c
recursive_int *recursive_int_abs(recursive_int *)
```

Changes all the values inside the given `recursive_int` to be absolute.

NOTE: this only works like the absolute value when the given `recursive_int` has no sign-alterations in terms.

&nbsp;

```c
recursive_int *recursive_int_addinv(recursive_int *)
```

Takes the additive inverse of all the terms within the given `recursive_int`.

&nbsp;

```c
recursive_int *recursive_int_inc(recursive_int *)
```

Increments the given recursive integer in the following fashion - if its top is above `LLONG_MAX`, then it allocates a new `recursive_int` based of the given one with the `value` of `1` and returns a pointer to it. Otherwise - just adds one to the top layer of the `recursive_int`.

Preserves optimized-ness for positive values only.

&nbsp;

```c
recursive_int *recursive_int_dec(recursive_int *)
```

A decrement of the given `recursive_int` defined in the same fashion as `recursive_int_inc`, except for now one is checking for `LLONG_MIN`.

Preserves optimizedness for negative values only.

&nbsp;

```c
recursive_int *recursive_zero()
```

Allocates and returns a pointer to the `recursive_int` equivalent of `0`.

&nbsp;

```c
recursive_int *recursive_int_from_ll(long long v)
```

An alias for allocation of a new `recursive_int` of depth `1` with `value` of `v` (direct conversion from `long long`).

&nbsp;

```c
recursive_int *get_negative(recursive_int * ri)
```

Allocates and returns a new `recursive_int`, such that it contains only all the negative terms of `ri`.

&nbsp;

```c
recursive_int *get_positive(recursive_int *)
```

Same as `get_negative`, but for positive terms.

&nbsp;

```c
recursive_int *first_not_full(recursive_int * ri)
```

Returns the first sub-integer of `ri` such that its values are neither of `LLONG_MAX` and `LLONG_MIN`.

&nbsp;

```c
recursive_int *last_not_full(recursive_int * ri)
```

Returns the last sub-integer of `ri` such that its values are neither of `LLONG_MAX` and `LLONG_MIN`.

&nbsp;

```c
recursive_int *recursive_int_last(recursive_int * ri)
```

Returns the last sub-integer of `ri`.

&nbsp;

```c
recursive_int *recursive_int_set_last(recursive_int * ri, recursive_int * newlast)
```

Replaces the current last sub-integer of `ri` with `newlast`. Returns the pointer to the discarded one.

&nbsp;

```c
recursive_int *recursive_int_depth(recursive_int *)
```

Returns the number of summands inside of the given `recursive_int`.

&nbsp;

```c
recursive_int *recursive_int_revert(recursive_int *)
```

Reverts the order of summands inside the given recursive_int.

&nbsp;

#### `optimized.h`

This header file includes all of the methods and definitions from `base.h`.

##### Methods

```c
recursive_int *recursive_int_optimize(recursive_int *)
```

"Optimizes" a given `recursive_int`. Eliminates all:

1. Sign alterations
2. Terms that are not equal to `LLONG_MAX` or `LLONG_MIN` (up to 1).
3. Terms that are equal to `0`.

While preserving the final value of the `recursive_int`.

The optimized versions are far more memory efficient, are easier to work with and cause solutions to certain algorithms to become trivial.
The only downside to using them is the necessity for explicit conversion before doing doing anything futher (which can be more costly time-wise).

On the other hand, the unoptimized operations are simpler to implement, but are more resource-costly (unneeded allocated space).

&nbsp;

```c
recursive_int *recursive_int_diff(recursive_int *, recursive_int *)
```

Difference between two `recursive_int`s without sign alteration (preserves optimized-ness).

&nbsp;

```c
recursive_int *recursive_int_sum(recursive_int *, recursive_int *)
```

Sum between two `recursive_int`s without sign alteration (preserves optimized-ness).

&nbsp;

```c
bool greateroe(long long x, long long y);
```

A functional equivalent of `x >= y`.

&nbsp;

```c
bool lesseroe(long long x, long long y);
```

A functional equivalent of `x <= y`.

&nbsp;

```c
recursive_int *recursive_int_minimize(recursive_int *)
```

Eliminates all the `0`s and other non-`LLONG_MAX`/non-`LLONG_MIN` values (up to 1)
with preservation of the final value of the sum (it does that by means of 'shrinking' the sum's value);

NOTE: the only possible value that is non-`LLONG_MAX`/non-`LLONG_MIN` is at the BOTTOM (end) of the linked list.
This way, this first has got to be reversed with `recursive_int_optimized_revert`.

&nbsp;

```c
bool recursive_int_equal_optimized(recursive_int *, recursive_int *)
```

Checks whether two optimized `recursive_int`s are equal.

&nbsp;

```c
bool optimized_is_zero(recursive_int *)
```

Checks whether the given optimized `recursive_int` is zero.

&nbsp;

```c
recursive_int *recursive_int_optimized_revert(recursive_int *)
```

Reverts the order of summands inside the given optimized `recursive_int`.

NOTE: in practice, all it does is change the first and last nodes places, returning the pointer to the new first one.
For optimized values, this is a sum-equivalent of a full revert.

&nbsp;

#### `recursive_int.h`

This header file includes all the definitions and methods from `optimized.h`.

##### Methods

```c
recursive_int *recursive_int_add(recursive_int *, recursive_int *)
```

Sum between two `recursive_int`s - does not allocate a new one (only links the latter to the former one's end). Does not (generally) preserve optimizedness.

&nbsp;

```c
recursive_int *recursive_int_add_i(recursive_int *, long long value)
```

Same as `recursive_int_add`, but first allocates a new `recursive_int` from `value`.

&nbsp;

```c
recursive_int *recursive_int_mult(recursive_int *, recursive_int *)
```

Returns the product of two `recursive_int`s (works with unoptimized ones).

&nbsp;

```c
bool recursive_int_greater(recursive_int *, recursive_int *)
```

Returns which of the two `recursive_int`s is greater (works with unoptimized ones).

&nbsp;

```c
bool recursive_int_equal(recursive_int *, recursive_int *)
```

Returns whether two `recursive_int`s are equal (works with unoptimizd ones).

&nbsp;

```c
bool recursive_int_sign(recursive_int * ri)
```

Returns `1` if `ri` is positive or `0` and `0` otherwise.

&nbsp;

```c
bool is_zero(recursive_int *)
```

Returns whether the given `recursive_int` is zero (works with un-optimized values as well).

&nbsp;

```c
bool recursive_int_llfit(recursive_int *)
```

Returns the boolean indicating whether the given `recursive_int` fits into a single `long long`.

&nbsp;

#### `print.h`

Methods related to printing of the values of `recursive_int` (mainly for debug purposes).

##### Macros

```c
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
```

##### Methods

```c
wchar_t *string_reverse(wchar_t *)
```

Allocates a new `wchar_t` array, the value of which is the reversal of the given one, and then returns pointer to it.

&nbsp;

```c
wchar_t *base_representation(long long number, unsigned short base)
```

Allocates a new `wchar_t *`, pointing to the symbolic representation of `number` in `base`.

NOTE: the UTF-16 values are used for construction of symbols for every given `base`.

&nbsp;

```c
wchar_t *symbolic_bit_add(wchar_t *dest, wchar_t *add, long long pos, unsigned short base)
```

"Adds" symbolicaly the last item of the `wchar_t` pointer `add`
to `dest` at position `pos` (altering it) and subtracts the value from `add` (without altering it)
in base `base`. Returns `dest`.

NOTE: using a negative value for `pos` will cause the string to be reallocated and

&nbsp;

```c
wchar_t * symbolic_right_shift(whcar_t *dest);
```

Performs a shift of the data of `dest` to the 'right' (the end of the string);
The first element becomes `'0'`.

NOTE: this doesn't reallocate the `dest`, instead using the already present length;

&nbsp;

```c
wchar_t * symbolic_left_shift(whcar_t *dest);
```

A left (string beginning) equivalent of `symbolic_right_shift`.

&nbsp;

```c
bool symbolic_greater(wchar_t * a, wchar_t * b);
```

Compares two numbers' strings representations and returns whether the first is greater than the second.
Takes negativity into account.

```c
wchar_t *symbolic_new_size(wchar_t *total, size_t length);
```

Changes the symbolic "size" of the `total` to `length`.

```c
wchar_t *negate(wchar_t *a);
```

Allocates the negation of the value of `a` and returns it (handles multiple negative signs as well).

&nbsp;

```c
wchar_t *symbolic_bit_sub(wchar_t *dest, wchar_t *add, size_t pos, unsigned short base)
```

Same as `symbolic_bit_add`, but instead of addition does subtraction from `dest`.

&nbsp;

```c
wchar_t *symbolic_addition(wchar_t *, wchar_t *, unsigned short base);
```

Adds "symbolically" first and second argument (signs can differ) in base `base`,
then returns the pointer to the result as a newly allocated `wchar_t*`.

&nbsp;

```c
wchar_t *symbolic_subtraction(wchar_t *total, wchar_t *sub, unsigned short base);
```

Same as `symbolic_addition`, but for subtraction (also, does not work with negative values).

&nbsp;

```c
wchar_t *symbolic_plus(wchar_t *, wchar_t *);
```

Allocates and returns a new string which is the concatenation of the given two arguments with
either `"+"` or `"-"` (if the second one is negative).

&nbsp;

```c
wchar_t *recursive_int_print(recursive_int *, unsigned short base);
```

Allocates a new `wchar_t*`, containing the representation of a given `recursive_int` in base `base` and returns it.

&nbsp;

```c
wchar_t *recursive_int_print_sum(recursive_int *, unsigned short base);
```

Allocates a new `wchar_t*`, containing the representation of the given `recursive_int` as a sum of
`long long` values represented as `wchar_t*` in base `base`.
