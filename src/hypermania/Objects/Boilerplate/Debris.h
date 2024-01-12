#ifndef OBJ_DEBRIS_H
#define OBJ_DEBRIS_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
} ObjectDebris;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	int32 gravityStrength;
	int32 rotSpeed;
	Vector2 scaleSpeed;
	int32 delay;
	Animator animator;
} EntityDebris;

extern ObjectDebris* Debris;

// =============================================================================

// Functions -------------------------------------------------------------------

// =============================================================================
extern void (*Debris_State_Move)();
extern void (*Debris_State_FallAndFlicker)();

void Debris_Draw_OVERLOAD();

#define OBJ_DEBRIS_SETUP \
  MOD_REGISTER_OBJ_OVERLOAD(Debris, NULL, NULL, NULL, Debris_Draw_OVERLOAD, NULL, NULL, NULL, NULL, NULL)

#endif //! OBJ_DEBRIS_H
