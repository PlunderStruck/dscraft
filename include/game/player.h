#ifndef PLAYER_9
#define PLAYER_9

#include "game/map_types.h"
#include "game/player_types.h"

void loadSettings(void);
void saveSettings(void);
void initPlayer(player_struct* p);
void updatePlayer(player_struct* p);
void playerCamera(player_struct* p, bool environment);
void testPlane(map_struct* m, vect3D point, vect3D* vector);

#endif
