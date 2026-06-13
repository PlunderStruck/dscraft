#include "common/general.h"
#include "game/map_types.h"

char packPath[255];
char mapPath[255];

s16 cubeAngleX;

water_struct waterSpread[WATERNUMBER];
water_struct waterToSpread[WATERNUMBER2];
u32 waterCount, waterCursor;
u32 waterCount2, waterCursor2;

list_struct openList, closedList;

toProcessList_struct lightProcess;

u8 degradTable[8*8*5];
u8 lightTable[16*16*16*14];
u8 lightComputeTable[256*32];
u8 lightSun[6];

map_struct map;

u16 testquads;
s8 cursorDir;

vect3D waterAnim;
u32* uvMapCur;
u32* lightMapCur;
u32 uvMap[256*4];
u32 uvMapWater[4*6];
u32 lightMap[256*14];
u32 lightMap2[256*14];
u32 xyMap[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE*14*4];
u8 imIDtable[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
u8 jmIDtable[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
u8 kmIDtable[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
u32 ijkmIDtable2[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];

quad_struct* cache[CACHESIZE];
u16 cacheNumber;
u16 cacheCursor;
u16 cacheRecord;

lightsource_struct* lightCache[LIGHTCACHESIZE];
u16 lightCacheNumber;
u16 lightCacheCursor;
u16 lightCacheRecord;

u8 fogMode;

bool cull;

int TESTVALUE;
int TESTVALUE2;
int TESTVALUE3;
