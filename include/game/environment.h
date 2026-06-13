#ifndef ENVIRONMENT_9
#define ENVIRONMENT_9

#include "common/general.h"

#ifndef MTL_IMG_TYPEDEF
#define MTL_IMG_TYPEDEF
typedef struct MTL_img MTL_img;
#endif

#define STARS 32
// #define SUNSIZE 64
#define SUNSIZE 96
#define STARSIZE 5
#define DAWNSIZE 256
#define CLOUDSIZE 511

extern MTL_img *cloudTexture, *sunTexture, *moonTexture;

extern int sunX, sunZ;
extern int dayTime, nightTime;

extern u8 skyR, skyG, skyB;
extern u8 glareR, glareG, glareB;
extern u8 glareLength;

extern bool envMenu;
extern s16 cloudcnt;

void drawSky(void);
void drawSun(void);
void drawMoon(void);
void drawDawn(void);
void initStars(void);
void drawStars(void);
void drawCloud(void);
void freeEnvironment(void);
void initEnvironment(bool menu);

#endif
