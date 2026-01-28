#include "base.h"
#include "base_arena.h"
#include <stdio.h>
#define BASE_UNITY
#include "base_include.h"

typedef struct
{
  u64 x;
  u64 y;
  u64 z;

} object;

int main()
{
    mem_arena *arena = arena_create(KiB(8));

    object *obj = arena_alloc(arena, sizeof(object));

    obj->x = 1024;
    obj->y = 512;
    obj->z = 128;

#define debug
#ifdef debug
    breakpoint
#endif

    void *other = arena_alloc(arena, 8);

    obj->x = 1024;
    obj->y = 512;
    obj->z = 128;

    arena_destroy(arena);

    printf("%p", arena);

    return 0;
}
