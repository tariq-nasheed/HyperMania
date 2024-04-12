#pragma once

extern ObjectPlaneSeeSaw* PlaneSeeSaw;

bool32 PlaneSeeSaw_State_Launch_HOOK(bool32 skippedState);
bool32 PlaneSeeSaw_PlayerState_ToBG_HOOK(bool32 skippedState);

#define OBJ_PLANESEESAW_SETUP \
	HOOK_STATE(PlaneSeeSaw_State_Launch, 1); \
	HOOK_STATE(PlaneSeeSaw_PlayerState_ToBG, 0); \
	MOD_REGISTER_OBJ_OVERLOAD(PlaneSeeSaw, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)
