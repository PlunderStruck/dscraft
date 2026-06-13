#ifndef MAP_TYPES_9
#define MAP_TYPES_9

#include "common/general.h"
#include "game/block_types.h"
#include "game/vect3D.h"

#define LADDERTYPE 40
#define DOORTYPE 44

#define BLOCKTEXTURES 45
#define BLOCKS 46

#ifdef FOGLIGHT
	#define LIGHTAMBIENT 4
	#define LIGHTAMBIENT2 7
	#define SUNAMBIENT 10
#else
	#define LIGHTAMBIENT 10
	#define LIGHTAMBIENT2 10
	#define SUNAMBIENT 6
#endif
#define MOONLIGHT 8

#define CACHESIZE 1024*50
#define CACHEBLOCK 64

#define LIGHTCACHESIZE 1024*4
#define LIGHTCACHEBLOCK 1024

#define WATERNUMBER 8*1024
#define WATERNUMBER2 4*1024
#define WATERMIN 8
#define WATERMAX 120
#define WATERSPREAD 6

#define CLUSTERSIZE 4
#define SUPERCLUSTERSIZE 32

#define LISTSIZE 4096
#define SCALEFACTOR 32
#define tilesize 1
#define tilesize2 (tilesize*2)
#define bsize ((tilesize2*CLUSTERSIZE)<<6)
#define bsizeR ((tilesize2*CLUSTERSIZE))
#define max(a,b) ((a)<(b))?(b):(a)
#define min(a,b) ((a)>(b))?(b):(a)
#define qgetBlock(m, i, j, k) (m)->data[(i)+(j)*(m)->size.x+(k)*(m)->size.y*(m)->size.x]
// #define qgetCluster(m, i, j, k) ((i)+(j)*(m)->clusterSize.x+(k)*(m)->clusterSize.y*(m)->clusterSize.x)
#define qgetCluster(m, i, j, k) ((i)+(j)*SUPERCLUSTERSIZE+(k)*SUPERCLUSTERSIZE*SUPERCLUSTERSIZE)

#define rTilesize ((tilesize*SCALEFACTOR)<<6)
#define rTilesize2 ((tilesize2*SCALEFACTOR)<<6)

#define dir_x (1)
#define dir_y (1<<1)
#define dir_z (1<<2)

#define dir_up (1)
#define dir_down (1<<1)
#define dir_left (1<<2)
#define dir_right (1<<3)
#define dir_front (1<<4)
#define dir_behind (1<<5)

#define t1 NORMAL_PACK(-32,-32,0)
#define t2 NORMAL_PACK(-32,32,0)
#define t3 NORMAL_PACK(32,32,0)
#define t4 NORMAL_PACK(32,-32,0)

extern bool testBuffer;

typedef struct
{
	u16 sizeX, sizeY;
	u32 magicVersionNumber;
	u16 spawnX, spawnY;
	s32 spawnZ;
}header_struct;

typedef struct
{
	s8 i, j, k;
	void* next;
} __attribute__((__packed__)) lightsource_struct;

typedef struct
{
	// lightsource_struct *first;//, *last;
	void *first;//, *last;
	u8 count;
}lightsourceList_struct;

typedef struct
{
	// u8 i, j, k;
	u8 mID;
	u8 direction, type, light;
	// u16 lID;
	void* next;
} __attribute__((__packed__)) quad_struct;

typedef struct
{
	quad_struct *first;//, *last;
	u16 count;
}quadList_struct;

typedef struct
{
	quadList_struct quadList, specialList;
	lightsourceList_struct lightList;
	u8 wall;
	// u8 data[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
	// u32 draw; //u8
	// u32* list;
}cluster_struct;

typedef struct
{
	u8 data[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE*16];
	u8 highest[CLUSTERSIZE*CLUSTERSIZE];
	cluster_struct cluster[16];
	u8 changed;
}clusterColumn_struct;

typedef struct
{
	header_struct* header;
	vect3D size, clusterSize, offset;
	// u8* data;
	// quadList_struct quadList;
	// cluster_struct* clusterz;
	// cluster_struct* superCluster[32][32];
	clusterColumn_struct* superCluster[32][32];
	clusterColumn_struct* transitionCluster[4*32];
	// u8 transitionStuff[4*(4*4*4*16)*32];
	u8 transitionStuff[4*4*4*16];
	u8 transitioning[4];
	// u32 clusterDraw[SUPERCLUSTERSIZE*SUPERCLUSTERSIZE*16];
	u16 clusterDraw[SUPERCLUSTERSIZE*SUPERCLUSTERSIZE*16];
	u16 clusterDrawn[SUPERCLUSTERSIZE*SUPERCLUSTERSIZE*16];
	// FILE_POSITION* fileMap;
	u32* headerMap;
	u32* fileMap;
	void* fileHandle;
}map_struct;

typedef struct
{
	u16 i, j, k;
	u8 direction;
	// void* next;
}listElement_struct;

typedef struct
{
	// listElement_struct* first;
	// listElement_struct** last;
	listElement_struct elements[LISTSIZE];
	u16 size;
}list_struct;

typedef struct
{
	u16 i, j, k;
	void* next;
}toProcess_struct;

typedef struct
{
	// toProcess_struct* first;
	void* first;
	u16 count;
}toProcessList_struct;

typedef struct
{
	u32 pos;
	// u8 dir;
} __attribute__((__packed__)) water_struct;

extern const block_struct blocks[];
extern const blockTex_struct blockTextures[];

extern char packPath[255];
extern char mapPath[255];

extern s16 cubeAngleX;

extern water_struct waterSpread[WATERNUMBER];
extern water_struct waterToSpread[WATERNUMBER2];
extern u32 waterCount, waterCursor;
extern u32 waterCount2, waterCursor2;

extern list_struct openList, closedList;

extern toProcessList_struct lightProcess;

extern u8 degradTable[8*8*5];
// u8 lightTable[13*13*13*6];
extern u8 lightTable[16*16*16*14];
extern u8 lightComputeTable[256*32];
extern u8 lightSun[6];

extern map_struct map;

extern u16 testquads;
extern s8 cursorDir;

extern vect3D waterAnim;
extern u32* uvMapCur;
extern u32* lightMapCur;
extern u32 uvMap[256*4];
extern u32 uvMapWater[4*6];
extern u32 lightMap[256*14];
extern u32 lightMap2[256*14];
extern u32 xyMap[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE*14*4];
extern u8 imIDtable[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
extern u8 jmIDtable[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
extern u8 kmIDtable[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
// u8 imIDtable2[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
// u16 jmIDtable2[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
// u16 kmIDtable2[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];
extern u32 ijkmIDtable2[CLUSTERSIZE*CLUSTERSIZE*CLUSTERSIZE];

extern quad_struct* cache[CACHESIZE];
extern u16 cacheNumber;
extern u16 cacheCursor;
extern u16 cacheRecord;

extern lightsource_struct* lightCache[LIGHTCACHESIZE];
extern u16 lightCacheNumber;
extern u16 lightCacheCursor;
extern u16 lightCacheRecord;

extern u8 fogMode;

extern bool cull;

extern int TESTVALUE;
extern int TESTVALUE2;
extern int TESTVALUE3;

#endif
