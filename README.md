<!-- TODO: write documentation for methods! [and test them based on it...] -->
<!-- TODO: create a file for testing of each one separate method - DO IT FROM GROUNDS UP, draw a dependency graph and test from top-to-bottom...; -->

# recursive_int

This is a small C library that wholy implements Integers via recursion.
There is no inherent max possible size of the integers allocatable with it,
only limitations are due to the user's RAM.

## Documentation

### Definition

The "recursive integers" are basically linked lists, representing their sums.
From this definition various properties sprout and the library contains the methods
needed to acommodate some of them.

### Headers

1. `base.h` - contains basic operations on the recursive_int structure (also the structure itself);
2. `optimized.h` - most of operations in `base.h` are on "unoptimized" integers (those that can contain sign alterations and zeros); Contains operations related to optimizing them (saves memory, takes additional time to do, but make writing algorithms a lot easier).
3. `recursive_int.h` - methods that depend upon `optimized.h`, but don't relate to optimization itself.

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
recursive_int *alloc_recursive_int(long long v, recursive_int *)
```

```c
recursive_int *free_recursive_int(recursive_int *)
```

```c
recursive_int *recursive_int_copy(recursive_int *)
```

```c
recursive_int *recursive_int_abs(recursive_int *)
```

```c
recursive_int *recursive_int_addinv(recursive_int *)
```

```c
recursive_int *recursive_int_inc(recursive_int *)
```

```c
recursive_int *recursive_int_dec(recursive_int *)
```

```c
recursive_int *recursive_zero()
```

```c
recursive_int *get_negative(recursive_int *)
```

```c
recursive_int *get_positive(recursive_int *)
```

```c
recursive_int *first_not_full(recursive_int *)
```

```c
recursive_int *last_not_full(recursive_int *)
```

```c
recursive_int *recursive_int_last(recursive_int *)
```

```c
recursive_int *recursive_int_set_last(recursive_int *, recursive_int *)
```

```c
recursive_int *recursive_int_depth(recursive_int *)
```

```c
recursive_int *recursive_int_revert(recursive_int *)
```

#### `optimized.h`

This header file includes all of the methods and definitions from `base.h`.

##### Methods

```c
recursive_int *recursive_int_optimize(recursive_int *)
```

```c
recursive_int *recursive_int_diff(recursive_int *, recursive_int *)
```

```c
recursive_int *recursive_int_sum(recursive_int *, recursive_int *)
```

```c
recursive_int *recursive_int_minize(recursive_int *)
```

```c
recursive_int *recursive_int_minize_positive(recursive_int *)
```

```c
recursive_int *recursive_int_minize_negative(recursive_int *)
```

```c
bool recursive_int_equal_optimized(recursive_int *, recursive_int *)
```

```c
bool optimized_is_zero(recursive_int *)
```

```c
recursive_int *recursive_int_optimized_revert(recursive_int *)
```

```c
bool recursive_int_llfit(recursive_int *)
```

#### `recursive_int.h`

This header file includes all the definitions and methods from `optimized.h`.

##### Methods

```c
recursive_int *recursive_int_add(recursive_int *, recursive_int *)
```

```c
recursive_int *recursive_int_add_i(recursive_int *, long long)
```

```c
recursive_int *recursive_int_mult(recursive_int *, recursive_int *)
```

```c
bool recursive_int_greater(recursive_int *, recursive_int *)
```

```c
bool recursive_int_equal(recursive_int *, recursive_int *)
```

```c
bool recursive_int_sign(recursive_int *)
```

```c
recursive_int *recursive_int_depth(recursive_int *)
```
