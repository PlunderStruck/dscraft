#ifndef __STATE_TYPES9__
#define __STATE_TYPES9__

typedef void(*function)();

typedef struct DS_state {
	function Init,Frame,Kill,VBlank;
	u16 mc_id;
	u8 id;
	bool used;
	int notusedtest;
} DS_state;

#endif
