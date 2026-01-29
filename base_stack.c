#include "base_stack.h"
#include "base_mem.h"

internal mem_stack *
stack_create(u64 capacity)
{
    mem_stack *stack = (mem_stack *)mmap(
    NULL,
    capacity + sizeof(mem_stack),
    PROT_READ | PROT_WRITE,
    MAP_SHARED | MAP_ANONYMOUS,
    -1,
    0);

    if (stack == MAP_FAILED)
    {
        return NULL;
    }

    stack->capacity = capacity;

    stack->base_position = (u8 *)stack +
                           sizeof(mem_stack) +
                           sizeof(mem_stack_header);
    stack->current_position = 0;

    return stack;
}

internal umm
calc_padding_with_header(umm ptr, umm alignment, umm header_size)
{
    umm p, a, modulo, padding, needed_space;

    if (!is_pow(alignment))
    {
        return 0;
    }

    p            = ptr;
    a            = alignment;
    modulo       = p & (a - 1);
    padding      = 0;
    needed_space = 0;

    if (0 == modulo)
    {
        padding = a - modulo;
    }

    needed_space = (umm)header_size;
    if (padding < needed_space)
    {
        needed_space -= padding;

        if ((needed_space & (a - 1)) != 0)
        {
            padding += a * (1 + (needed_space / a));
        }
        else
        {
            padding += a * (needed_space / a);
        }
    }

    return (umm)padding;
}

internal mem_stack *
stack_push_align(mem_stack *stack, u64 size, umm alignment)
{
    umm               current_address, next_address;
    umm               padding;
    mem_stack_header *header;

    if (!is_pow(alignment))
    {
        /**
         * TODO(nasr): error handling
         **/
        return 0;
    }

    if (alignment > 128)
    {
        alignment = 128;
    }

    current_address = (umm)stack->base_position + stack->current_position;
    padding         = calc_padding_with_header(padding, alignment, sizeof(mem_stack_header));
    if (stack->current_position + padding + size > stack->capacity)
    {
        return 0;
    }

    stack->current_position += padding;

    next_address    = current_address + (umm)padding;
    header          = (mem_stack_header *)(next_address - sizeof(mem_stack_header));
    header->padding = (u8)padding;

    stack->current_position += size;

    return MemSet((void *)next_address, size);
}

internal void *
stack_push(mem_stack *stack, umm size)
{
    return stack_push_align(stack, size, ARENA_ALIGN);
}

internal void
stack_pop(mem_stack *stack, void *pointer)
{
    if (pointer != NULL)
    {
        umm               start, end, current_address;
        mem_stack_header *header;
        umm               prev_offset;

        start           = (umm)stack->base_position;
        end             = start + (umm)stack->capacity;
        current_address = (umm)pointer;

        if (!(start <= current_address && current_address < end))
        {
            if (0 && "Out of bounds memory address passed to stack allocator (free)")
            {
                return;
            }
            return;
        }

        if (current_address >= start + (umm)stack->base_position)
        {
            return;
        }

        header                  = (mem_stack_header *)(current_address - sizeof(mem_stack_header));
        prev_offset             = (size_t)(current_address - (umm)header->padding - start);
        stack->current_position = prev_offset;
    }
    return;
}

internal mem_stack *
stack_resize_align(mem_stack *stack, void *pointer, u64 old_size, u64 new_size, u64 alignment)
{
    if (pointer == NULL)
    {
        return stack_push_align(stack, new_size, alignment);
    }
    else if (new_size == 0)
    {
        stack_pop(stack, pointer);
        return NULL;
    }

    umm   start, end, current_address;
    umm   min_size = old_size < new_size ? old_size : new_size;
    void *new_pointer;

    start           = (umm)stack->base_position;
    end             = start + (umm)stack->capacity;
    current_address = (umm)pointer;
    if (!(start <= current_address && current_address < end))
    {
        check(0);
        return NULL;
    }

    if (current_address >= start + (umm)stack->current_position)
    {
        // Treat as a double free
        return NULL;
    }

    if (old_size == new_size)
    {
        return pointer;
    }

    new_pointer = stack_push_align(stack, new_size, alignment);
    memmove(new_pointer, pointer, min_size);
    return new_pointer;
}

internal void
stack_pop_all(mem_stack *stack)
{
    stack->current_position = 0;
}

internal void
stack_destroy(mem_stack *stack)
{
    if (!stack)
    {
        return;
    }

    int res = munmap(stack, stack->capacity + sizeof(mem_stack));
    check(res);
}
