#ifndef __GENMATH9__
#define __GENMATH9__

// #define min(a,b) (((a)>(b))?(b):(a))
// #define max(a,b) (((a)>(b))?(a):(b))

//Original code by Mollusk

int ArcTan2(int dx, int dy);

#include "common/math_lookup.h"

u16 Math_AdjustAngle(u16 angle, s16 anglerot, s32 startx, s32 starty, s32 targetx, s32 targety);

#endif
