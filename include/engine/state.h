#ifndef __STATE9__
#define __STATE9__

#include "engine/state_types.h"

extern u8 state_id;

extern DS_state *CurrentState, *NextState;

extern DS_state Game_State, Menu_State;

void glReInit(void);
void DS_ApplyState(void);
void DS_InitHardware(void);
void DS_SetState(DS_state* state);

static inline void DS_ChangeState(DS_state* state)
{
	if(CurrentState)CurrentState->used=0;
	NextState=state;
}

void DS_CreateState(DS_state* state, function Init, function Frame, function Kill, function VBlank);

#endif
