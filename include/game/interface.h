#ifndef INTERFACE_9
#define INTERFACE_9

#include "common/general.h"

extern bool invOpen, overButtons;

void initItems(void);
void initItemBar(void);
void initInterface(void);
void loadInterface(char* filename, u8 prio);
bool updateInterface(void);
bool getItemBlockForSlot(u8 slot, u8* block);

#endif
