#ifndef MAP_IO_9
#define MAP_IO_9

#include "game/map_types.h"

bool readSectors(u32 sector, u32 number, u8* buffer);
bool writeSectors(u32 sector, u32 number, u8* buffer);

void initFilesystem(void);

extern void (*readClusterColumn)(map_struct*, u16, u16, clusterColumn_struct*, u8*, void*);
void readClusterColumn2048(map_struct*, u16, u16, clusterColumn_struct*, u8*, void*);
void readClusterColumn1024(map_struct*, u16, u16, clusterColumn_struct*, u8*, void*);
void readClusterColumn512(map_struct*, u16, u16, clusterColumn_struct*, u8*, void*);
void readClusterColumnNOCASH(map_struct*, u16, u16, clusterColumn_struct*, u8*, void*);

extern void (*writeClusterColumn)(map_struct* m, u16 i, u16 j, clusterColumn_struct* c, u8* t, void* f);
void writeClusterColumn2048(map_struct* m, u16 i, u16 j, clusterColumn_struct* c, u8* t, void* f);
void writeClusterColumn1024(map_struct* m, u16 i, u16 j, clusterColumn_struct* c, u8* t, void* f);
void writeClusterColumn512(map_struct* m, u16 i, u16 j, clusterColumn_struct* c, u8* t, void* f);
void writeClusterColumnNOCASH(map_struct* m, u16 i, u16 j, clusterColumn_struct* c, u8* t, void* f);

extern void (*openMap)(char*, map_struct*);
void openMap2048(char*, map_struct*);
void openMap1024(char*, map_struct*);
void openMap512(char*, map_struct*);
void openMapNOCASH(char*, map_struct*);

void globalSaveMap(map_struct* m);
void createTestMap(map_struct* m);
void translateSuperCluster(map_struct* m, u8 dir);

#endif
