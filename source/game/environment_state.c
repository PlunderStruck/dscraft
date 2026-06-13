#include "common/general.h"
#include "game/environment.h"

star_struct stars[STARS];

MTL_img *cloudTexture, *sunTexture, *moonTexture;

int sunX, sunZ;
int dayTime, nightTime;

u8 skyR, skyG, skyB;
u8 glareR, glareG, glareB;
u8 glareLength;

bool envMenu;
s16 cloudcnt;
