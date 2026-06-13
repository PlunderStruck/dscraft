#ifndef _STATS_H
#define _STATS_H

#include "debug/stats_types.h"

extern stats_struct streamRead;
extern stats_struct streamCalc;
extern stats_struct columnWrite;
extern stats_struct frameTime;
extern stats_struct freeRam;

void initStats(stats_struct* s);
void addValue(stats_struct* s, u32 value);
void writeStats(stats_struct* s, char* name, char* filename);

#endif 
