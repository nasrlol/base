#include "base_arena.h"

/**
* NOTE(nasr): * check if the pointer is a
* power of 2, * will be used to determine if the memory
* is already aligned, or if we should align it
**/
internal inline b8
is_pow(umm x)
{
    return (x & (x - 1)) == 0;
}

internal inline u64
align(u64 ptr, umm align)
{
    if (is_pow)
    {
        return ptr;
    }

	(ptr & (ptr - 1)) == 0;

    umm a, modulo;

    /** 
	* we could do a regular (p % a) but this is faster because
	* a is already a power of 2
	*/
    a = (umm)align;
    modulo = ptr & (a - 1);

    if (modulo != 0)
    {
        ptr += a - modulo;
    }

    return p;
}

internal mem_arena *
arena_create(u64 capacity)
{
    mem_arena *arena = (mem_arena *)mmap(
        /* kernel decides where to throw the arena */
    NULL,
    capacity,
    PROT_READ | PROT_WRITE | PROT_EXEC,
    MAP_SHARED | MAP_ANONYMOUS,
    -1,
    0);

    if (arena == MAP_FAILED)
    {
        return NULL;
    }

    arena->capacity = capacity;
    arena->pos      = sizeof(*arena);
    arena->prev_pos = sizeof(*arena);

    return arena;
}

/*
 * make it a void pointer to allow implicit conversion
 * */
internal void
arena_destroy(mem_arena *arena)
{
    munmap(arena, arena->capacity);
}

internal void *
arena_alloc(mem_arena *arena, u64 size)
{
    u64 pos_aligned = ALIGN_UP_POW2(arena->pos, ARENA_ALIGN);
    u64 new_pos     = pos_aligned + size;

    if (new_pos > arena->capacity)
    {
        assert(0);
        /* NOTE(nasr): this means that the arena ran out of memory */
        return NULL;
    }

    arena->pos = new_pos;
    u8 *out    = (u8 *)arena + pos_aligned;

    memset(out, 0, size);
    return out;
}

internal void
arena_pop(mem_arena *arena, u64 size)
{
    size = MIN(size, arena->pos - sizeof(*arena));
    arena->pos -= size;
}

internal void
arena_pop_to(mem_arena *arena, u64 pos)
{
    u64 size = pos < arena->pos ? arena->pos - pos : 0;
    arena_pop(arena, size);
}

internal void
arena_clear(mem_arena *arena)
{
    arena_pop_to(arena, sizeof(*arena));
}

internal void
arena_resize(mem_arena *arena)
{
    check(is_aligned(arena->pos));
}

internal temp_arena
temp_arena_begin(mem_arena *arena)
{
    temp_arena temp;
    temp.arena       = arena;
    temp.prev_offset = arena->prev_pos;
    temp.offset      = arena->pos;

    return temp;
}

internal void
temp_arena_end(temp_arena temp)
{
    temp.arena->prev_pos = temp.prev_offset;
    temp.arena->pos      = temp.offset;
}

internal void
stack_create(u64 size)
{
    /*TODO(nasr)*/
}

internal void
stack_destroy(u64 size)
{
}
