#ifndef _STATS_TYPES_H
#define _STATS_TYPES_H

#include <nds.h>

typedef struct
{
	u32 total;
	u32 max, min;
	u32 count;
}stats_struct;

#endif
