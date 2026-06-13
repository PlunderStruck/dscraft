#ifndef MAP_RENDER_9
#define MAP_RENDER_9

#include "game/map_types.h"

void loadBlockTextures(bool spr, bool tex);
void Map_ApplyBlockSuperTexture(void);
void Map_ApplyCrossHair(void);
void generateMapQuadList(map_struct* m);
void updateLightMap(void);
void setFog(u8 mode);
void drawTestCube(void);
void renderClusterList(map_struct* m, int x, int y, int z);
void drawTestCluster(cluster_struct* c, int i, int j, int k);

#endif
