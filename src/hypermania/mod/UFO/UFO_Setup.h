#pragma once

extern ObjectUFO_Setup *UFO_Setup;

typedef struct {
	int32 timedOut;
	int32 machLevel;
	int32 scoreBonus;
	int32 rings;
	int32 specialStageID;
} UFO_HPZbuffer_t;

extern UFO_HPZbuffer_t UFO_HPZbuffer;

bool32 UFO_Setup_State_FinishFadeout_HOOK(bool32);

extern void (*UFO_Setup_State_FinishFadeout)();
extern void (*UFO_Setup_Finish_Win)();

void SetupHPZResults(void* data);

// lol
#define OBJ_UFO_SETUP_SETUP \
  Mod.AddModCallback(MODCB_ONUPDATE, SetupHPZResults); \
  IMPORT_PUBLIC_FUNC(UFO_Setup_State_FinishFadeout); \
  IMPORT_PUBLIC_FUNC(UFO_Setup_Finish_Win); \
  HOOK_IMPORTED_STATE(UFO_Setup_State_FinishFadeout, 1); \
  MOD_REGISTER_OBJECT_HOOK(UFO_Setup)
