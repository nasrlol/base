#include "base_mem.h"

/////////////////////////////////////////////////////////////////////////////
internal inline b8
is_pow(umm x)
{
    return (x & (x - 1)) == 0;
}
internal inline u64
align(u64 ptr, umm alignment)
{
    check((alignment & (alignment - 1)) == 0);
    return (ptr + alignment - 1) & ~(alignment - 1);
}

/////////////////////////////////////////////////////////////////////////////
