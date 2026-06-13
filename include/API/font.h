#ifndef __FONT9__
#define __FONT9__

#include "game/textures.h"

#define CHARSIZE 16

void loadAPIFont(void);
void drawChar(char c, u16 color, s32 x, s32 y);
void drawString(char* s, u16 color, s32 size, s32 x, s32 y);

#endif
