/*
 *	xmem.c
 *	  part of the xlibrary by SunDEV (http://sundev.890m.com)
 *
 *	Changelog :
 *	  21-03-09 : First public release
 *
 */

#include <nds.h>
#include <stddef.h>
#include <malloc.h>
#include <unistd.h>

static size_t latestUsed, latestFree;

extern u8 __end__[];        // end of static code and data

u8 *getHeapStart() {
	return __end__;
}

u8 *getHeapEnd() {
	return (u8 *)sbrk(0);
}

u8 *getHeapLimit() {
	return (u8*)0x02400000;
}

size_t getMemUsed() {
	struct mallinfo mi = mallinfo();
	latestUsed=mi.uordblks;
	return latestUsed;
}

size_t getMemFree() {
	struct mallinfo mi = mallinfo();
	latestFree=mi.fordblks + (getHeapLimit() - getHeapEnd());
	return latestFree;
}
