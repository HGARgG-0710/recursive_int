// ! Order definitions inside the file...;

#include "recursive_int.h"

typedef struct
{
	void *memory;
	recursive_int *status;
} paralloc_result;

paralloc_result *paralloc(recursive_int *);
void parfree(paralloc_result *);