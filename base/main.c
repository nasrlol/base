#include "base_include.h"


int main()
{

	mem_arena* arena = arena_create(KiB(8));
	printf("%p", arena);

	return 0;
}