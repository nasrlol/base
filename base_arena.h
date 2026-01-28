#ifndef ARENA_H
#define ARENA_H

#include "base.h"

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Arena Helper macro's
 * */

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define ALIGN(pointer, align) align((u64)(pointer), (umm)(align))
#define PUSH_STRUCT(arena, type) (type *)arena_alloc((arena), sizeof(type))
#define PUSH_ARRAY(arena, type, len) (type *)arena_alloc((arena), sizeof(type) * (len))
#define ARENA_ALIGN (2 * sizeof(void *))

typedef struct mem_arena  mem_arena;
typedef struct temp_arena temp_arena;

struct mem_arena
{
    u64 current_position;
    u64 previous_position;
    u64 capacity;
    u8 *base_position;
};

struct temp_arena
{
    mem_arena *arena;
    u64        start_position;
};

internal mem_arena *
arena_create(u64 capacity);

internal void
arena_destroy(mem_arena *arena);

internal void *
arena_alloc(mem_arena *arena, u64 size);

internal void
arena_clear(mem_arena *arena);

internal void
arena_clear(mem_arena *arena);

internal mem_arena *
arena_resize_align(mem_arena *arena, void *old_memory, u64 new_size, u64 old_size, umm alignment);

internal mem_arena *
arena_resize(mem_arena *arena, void *old_memory, u64 new_size, u64 old_size);

#endif
