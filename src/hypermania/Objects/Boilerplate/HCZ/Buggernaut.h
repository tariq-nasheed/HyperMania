#ifndef OBJ_BUGGERNAUT_H
#define OBJ_BUGGERNAUT_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxParentRange;
	uint16 aniFrames;
} ObjectBuggernaut;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	bool32 passThrough;
	int32 timer;
	int32 buzzCount;
	Vector2 startPos;
	Entity* parent;
	Animator bodyAnimator;
	Animator wingAnimator;
} EntityBuggernaut;

extern ObjectBuggernaut* Buggernaut;

void Buggernaut_EnemyInfoHook();

#define OBJ_BUGGERNAUT_SETUP \
  REGISTER_ENEMY(Buggernaut)

#endif //! OBJ_BUGGERNAUT_H
