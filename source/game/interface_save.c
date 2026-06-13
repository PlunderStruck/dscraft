#include "game/interface_save.h"

u8 buttonSprite;

void startSave(void)
{
	oamSub.oamMemory[buttonSprite+2*3].attribute[0] = ATTR0_COLOR_256 | ATTR0_WIDE | (80);
	oamSub.oamMemory[buttonSprite+2*3+1].attribute[0] = ATTR0_COLOR_256 | ATTR0_WIDE | (80);
	oamUpdate(&oamSub);
}

void endSave(void)
{
	oamSub.oamMemory[buttonSprite+2*3].attribute[0] = ATTR0_DISABLED;
	oamSub.oamMemory[buttonSprite+2*3+1].attribute[0] = ATTR0_DISABLED;
	oamUpdate(&oamSub);
}
