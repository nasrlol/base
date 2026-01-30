#define BASE_UNITY
#include "base_include.h"

#include <stdio.h>

#define debug

typedef struct object object;

struct object
{
    u64 x;
    u64 y;
    u64 z;
};

void
prints(mem_stack *stack)
{
    printf("stack: %p", stack);
    printf("base position %p", stack->base_position);
    printf("current position %lu", stack->current_offset);
    printf("previous position %lu", stack->capacity);
}

void
printa(mem_arena *arena)
{
    printf("arena: %p", arena);
    printf("base position %p", arena->base_position);
    printf("current position %lu", arena->current_position);
    printf("previous position %lu", arena->previous_position);
}

void
arena_test()
{
    mem_arena *arena = arena_create(KiB(8));

    object *obj = arena_alloc(arena, sizeof(object));

    printa(arena);

    obj->x = 1024;
    obj->y = 512;
    obj->z = 128;

    printa(arena);

    arena_destroy(arena);
}

void
stack_test()
{
    mem_stack *stack = stack_create(KiB(8));

    object *obj = stack_push(stack, sizeof(object));

    prints(stack);

    obj->x = 1024;
    obj->y = 512;
    obj->z = 128;

    stack_destroy(stack);

    prints(stack);
}

int
main()
{
    stack_test();
    return 0;
}
