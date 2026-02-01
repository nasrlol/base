#include "base.h"
#include "base_arena.h"
#include <sys/stat.h>
#define debug
#include "base_parse.h"
#undef debug

internal b8
compare_string(char *c1, char *c2)
{
    if (sizeof(c1) != sizeof(c2))
    {
        return -1;
    }

    for (
    u64 word_idx = 0;
    word_idx <= sizeof(*c1);
    ++word_idx)
    {
        if (*c1 != *c2)
        {
            return -1;
        }
        ++c1;
        ++c2;
    }

    return 0;
}

/**
 * Helper function to parse strings to int using ascii codes
 * */
internal u64
parse_u64(char *buf, umm len)
{
    u64 value = 0;

    for (umm buffer_idx = 0;
    buffer_idx < len;
    ++buffer_idx)
    {
        char c = buf[buffer_idx];
        if (c < '0' || c > '9')
        {
            break;
        }
        value = value * 10 + (c - '0');
    }

    return value;
}

/*

Get line count
and for each line
allocated an entry
and then for each \n
make a proc entry
and then iterate over the buffer


*/
internal ProcEntry *
parse_proc_files(char *path, mem_arena *arena)
{
    i32 line_count = 0;
    i32 fd         = open(path, O_RDONLY);
    if (fd < 0)
    {
        return NULL;
    }
    struct stat *file_info = PUSH_STRUCT(arena, struct stat);
    fstat(fd, file_info);
    char *buffer = PUSH_ARRAY(arena, char, KiB(4));
    u64   bytes  = read(fd, buffer, KiB(2));
    close(fd);

    for (u64 index = 0; index < bytes; ++index)
    {
        if (buffer[index] == '\n')
        {
            line_count++;
        }
    }

    ProcEntry *entries = arena_alloc(arena, sizeof(ProcEntry) * line_count);

    u32 entries_index = 0;
    u64 delim         = 0;

    for (u64 index = 0; index < bytes; ++index)
    {
        if (buffer[index] == ':')
        {
            delim = index;
        }
        else if (buffer[index] == '\n' && delim > 0)
        {
            MemCpy(entries[entries_index].key, buffer, delim);
            entries[entries_index].key[delim] = '\0';

            u64 start_offset = delim + 1;
            u64 end_offset   = index - delim - 1;
            MemCpy(entries[entries_index].value, buffer + start_offset, end_offset);
            entries[entries_index].value[end_offset] = '\0';

            entries_index++;
            delim = 0;
        }
    }
    return entries;
}

/*
 * is_numeric - Check if a string contains only digits
 * @s: String to check
 *
 * Return: 1 if string contains only numeric characters, 0 otherwise
 */
internal b8
is_numeric(char *s)
{
    for (; *s; ++s)
    {
        if (*s < '0' || *s > '9')
        {
            return 0;
        }
    }
    return 1;
}
