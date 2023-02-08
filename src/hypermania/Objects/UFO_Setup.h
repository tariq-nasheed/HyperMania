#ifndef OBJ_UFO_SETUP_H
#define OBJ_UFO_SETUP_H

#include "GameAPI/Game.h"

typedef struct {
    RSDK_OBJECT
    StateMachine(deformCB);
    int32 timedOut;
#if MANIA_USE_PLUS
    bool32 encoreStage;
#endif
    int32 machLevel;
    int32 scoreBonus;
    int32 machPoints;
    int32 rings;
    int32 timer;
    int32 ringFrame;
    int32 ringPan;
    int32 spherePan;
    int32 specialStageID;
    int32 machQuotas[3];
    uint8 playFieldLayer;
    uint16 sfxBlueSphere;
    uint16 sfxSSExit;
    uint16 sfxEmerald;
    uint16 sfxEvent;
    bool32 resetToTitle;
} ObjectUFO_Setup;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    color fadeColor;
} EntityUFO_Setup;

extern ObjectUFO_Setup *UFO_Setup;

typedef struct {
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

#endif //! OBJ_UFO_SETUP_H
