#include "base_parse.h"

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

internal ProcEntry *
parse_proc_files(char *path, mem_arena *arena)
{
    u64   fd, bytes;
    u64   index = 0;
    char *buffer;

    char KEY_DELIM      = ':';
    char VALUE_DELIMS[] = {
    ' ',
    '\t',
    };

    char RECORD_DELIM = '\n';

    ProcEntry *entry = PUSH_STRUCT(arena, ProcEntry);
    if (!path || !arena)
    {
        test(0);
        return NULL;
    }

    bytes = read(fd, &buffer, sizeof(buffer));

    while (index < bytes)
    {
        char *current_value = buffer;
        breakpoint

        ++ buffer;
    }

    close(fd);
    return entry;
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
