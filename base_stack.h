#ifndef STACK_H
#define STACK_H

#include <sys/mman.h>
#include <unistd.h>

#include "base.h"
#include "base_mem.h"

typedef struct mem_stack        mem_stack;
typedef struct mem_stack_header mem_stack_header;

struct mem_stack
{
    u8 *base_position;
    umm capacity;
    umm current_position;
};

struct mem_stack_header
{
    u8 padding;
    u8 previous_position;
};

#endif
