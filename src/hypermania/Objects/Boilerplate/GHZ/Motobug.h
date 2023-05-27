#ifndef OBJ_MOTOBUG_H
#define OBJ_MOTOBUG_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
} ObjectMotobug;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 turnTimer;
	int32 timer;
	Vector2 startPos;
	uint8 startDir;
	bool32 wasTurning;
	Animator animator;
} EntityMotobug;

extern ObjectMotobug* Motobug;

extern void (*Motobug_State_Smoke)();

void Motobug_EnemyInfoHook();

#define OBJ_MOTOBUG_SETUP \
  IMPORT_PUBLIC_FUNC(Motobug_State_Smoke); \
  REGISTER_ENEMY(Motobug)

#endif //! OBJ_MOTOBUG_H
