#ifndef PLAYER_TYPES_9
#define PLAYER_TYPES_9

#include "game/vect3D.h"

#define GRAVITY 70
#define BBSIZE 1000

typedef struct player_struct
{
	vect3D position, vector, clusterCoord;
	s16 angleZ, angleX;
	u8 inWater, onLadder, inCave;
} player_struct;

typedef struct settings_struct
{
	u8 controls;
	char texturePack[511];
} settings_struct;

extern settings_struct gameSettings;
extern player_struct Player;

extern s16 walkAngle;
extern s8 gravityDiv;

extern bool noclip;

extern u32 testCursor, testCursorI, testCursorJ, testCursorK;
extern u8 cursorBlock;

#endif
