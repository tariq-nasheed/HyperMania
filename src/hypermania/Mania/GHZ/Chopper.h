#ifndef OBJ_CHOPPER_H
#define OBJ_CHOPPER_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxJump;
	Hitbox hitboxSwim;
	Hitbox hitboxRange;
	Hitbox hitboxWater;
	uint16 aniFrames;
} ObjectChopper;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	uint16 timer;
	bool32 charge;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
} EntityChopper;

extern ObjectChopper* Chopper;

extern void (*Chopper_State_Jump)();

void Chopper_EnemyInfoHook();

#define OBJ_CHOPPER_SETUP \
  IMPORT_PUBLIC_FUNC(Chopper_State_Jump); \
  REGISTER_ENEMY(Chopper)

#endif //! OBJ_CHOPPER_H
