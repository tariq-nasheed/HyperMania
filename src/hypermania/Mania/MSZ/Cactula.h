#ifndef OBJ_CACTULA_H
#define OBJ_CACTULA_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
	uint16 sfxCactDrop;
} ObjectCactula;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 unused;
	int32 offsetY;
	bool32 droppedBomb;
	Animator bodyTopAnimator;
	Animator bodyBottomAnimator;
	Animator propellerAnimator;
} EntityCactula;

extern ObjectCactula* Cactula;

void Cactula_EnemyInfoHook();

#define OBJ_CACTULA_SETUP \
  REGISTER_ENEMY(Cactula)

#endif //! OBJ_CACTULA_H
