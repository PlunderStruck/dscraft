#ifndef MAP_API_9
#define MAP_API_9

#include "game/map_types.h"

void freeQuadCache(void);
void freeLightCache(void);
void initSuperCluster(map_struct* m);
void initMap(map_struct* m, vect3D size);
void addBlock(map_struct* m, int i, int j, int k);
bool addWater(map_struct* m, u16 i, u16 j, u16 k, u8 t);
void addQuad(quadList_struct* ql, map_struct* m, u8 direction, u8 light, u32 bid, u8* data, u16 i, u16 j, u16 k);
void removeBlock(map_struct* m, int i, int j, int k, bool fix);
void changeBlock(map_struct* m, int i, int j, int k, u8 type);
void fixGap(map_struct* m, int i, int j, int k);
void freeMap(map_struct* m);
void loadTestMap(map_struct* m);
vect3D getPointBlockPos(map_struct* m, s32 i, s32 j, s32 k);
u8 getPointBlock(map_struct* m, s32 i, s32 j, s32 k);

#endif
