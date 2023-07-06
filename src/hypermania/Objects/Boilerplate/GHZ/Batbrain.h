#ifndef OBJ_BATBRAIN_H
#define OBJ_BATBRAIN_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
	uint16 sfxFlap;
} ObjectBatbrain;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 targetY;
	EntityPlayer* target;
	Vector2 startPos;
	Animator animator;
} EntityBatbrain;

extern ObjectBatbrain* Batbrain;

void Batbrain_EnemyInfoHook();

#define OBJ_BATBRAIN_SETUP \
  REGISTER_ENEMY(Batbrain)

#endif //! OBJ_BATBRAIN_H
