#ifndef STACK_H
#define STACK_H

#include "base.h"

typedef struct
{
	/* NOTE(nasr): is this a pointer handle?  */

	u8* buf;
	umm buf_len;
	umm offset;


} mem_stack;

#endif
