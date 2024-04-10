#ifndef OBJ_SPINY_H
#define OBJ_SPINY_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxSpiny;
	Hitbox hitboxRange;
	Hitbox hitboxShot;
	uint16 aniFrames;
	uint16 sfxShot;
} ObjectSpiny;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Animator animator;
	int32 unused;
	uint8 type;
	Vector2 startPos;
	uint8 startDir;
	int32 shotVelocity;
	int32 dirChangeTimer;
	int32 moveTimer;
} EntitySpiny;

extern ObjectSpiny* Spiny;

extern void (*Spiny_State_Shot)();
extern void (*Spiny_State_ShotDisappear)();

void Spiny_EnemyInfoHook();

#define OBJ_SPINY_SETUP \
  IMPORT_PUBLIC_FUNC(Spiny_State_Shot); \
  IMPORT_PUBLIC_FUNC(Spiny_State_ShotDisappear); \
  REGISTER_ENEMY(Spiny)

#endif //! OBJ_SPINY_H
