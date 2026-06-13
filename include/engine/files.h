#ifndef __FILES9_H__
#define __FILES9_H__

#define ROOT "dscraft"

extern bool saveAvailable;
extern char* basePath;
extern int lastSize;
extern u8 fsMode;

int chdir (const char *path);
bool DS_InitFS(int argc, char **argv);
void* DS_OpenFile2 (char* filename, char* dir, bool binary);
void* DS_OpenFile (char* filename, char* dir, bool bufferize, bool binary);

#endif

