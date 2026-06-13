#ifndef MAP_PLAYER_9
#define MAP_PLAYER_9

#include "game/map_types.h"
#include "game/player_types.h"

void drawTestMapWithPlayer(map_struct* m, player_struct* player, void (*updatePlayerFn)(player_struct*), void (*playerCameraFn)(player_struct*, bool));

#endif
