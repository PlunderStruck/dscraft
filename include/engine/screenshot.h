#ifndef __SCREEN9__
#define __SCREEN9__

void Debug_TakeScreenshotBMP(u16* vram1, u16* vram2);
void D3D_SaveScreen(const char* filename, u16* buffer);
void D3D_TakeScreenshotBMP(u16* buffer);

#endif
