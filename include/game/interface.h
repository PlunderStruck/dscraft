#ifndef INTERFACE_9
#define INTERFACE_9

#include "common/general.h"

void initItems(void);
void initItemBar(void);
void initInterface(void);
void loadInterface(char* filename, u8 prio);
bool updateInterface(void);
bool getItemBlockForSlot(u8 slot, u8* block);
bool Interface_IsInventoryOpen(void);
bool Interface_IsOverButtons(void);
bool Interface_AllowsLookTouch(void);

#endif
