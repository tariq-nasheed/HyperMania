#ifndef OBJ_PLANESEESAW_H
#define OBJ_PLANESEESAW_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
	uint16 sfxSpring;
	uint16 sfxFlipper;
} ObjectPlaneSeeSaw;

// Entity Class
typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 unused;
	int32 seeSawPos;
	Animator platformAnimator;
	Animator swingAnimator;
	Animator weightAnimator;
} EntityPlaneSeeSaw;

extern ObjectPlaneSeeSaw* PlaneSeeSaw;

bool32 PlaneSeeSaw_State_Launch_HOOK(bool32 skippedState);
bool32 PlaneSeeSaw_PlayerState_ToBG_HOOK(bool32 skippedState);

#define OBJ_PLANESEESAW_SETUP \
	HOOK_STATE(PlaneSeeSaw_State_Launch, 1); \
	HOOK_STATE(PlaneSeeSaw_PlayerState_ToBG, 0); \
	MOD_REGISTER_OBJ_OVERLOAD(PlaneSeeSaw, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)

#endif //! OBJ_PLANESEESAW_H
