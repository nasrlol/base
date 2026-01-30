#ifndef BASE_PARSE_H
#define BASE_PARSE_H

#include "base.h"
#include "base_arena.h"

typedef struct string string;

struct string
{
    s8 *value;
    umm length;
};

typedef struct
{
    char *key;
    char *value[];
} ProcEntry;

typedef struct
{
    i8 *start;
    i8 *end;
    umm len;
} Line;

internal b8
compare_string(char *c1, char *c2);

internal ProcEntry *
parse_proc_files(char *path, mem_arena *arena);

internal u64
parse_u64(char *buf, umm len);

internal b8
is_numeric(char *s);

#endif
