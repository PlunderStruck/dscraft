#ifndef ENVIRONMENT_9
#define ENVIRONMENT_9

#include "common/general.h"

void drawSky(void);
void drawSun(void);
void drawMoon(void);
void drawDawn(void);
void initStars(void);
void drawStars(void);
void drawCloud(void);
void drawLogo(void);
void freeEnvironment(void);
void initEnvironment(bool menu);
void Environment_PrepareMenuSun(bool d3dScreen);
void Environment_ApplyMenuLight(void);
void Environment_AdvanceSun(s16 delta);
s16 Environment_GetSunSpriteAngle(void);
void Environment_AdvanceClock(s16 sunDelta, s16 cloudDelta);

#endif
