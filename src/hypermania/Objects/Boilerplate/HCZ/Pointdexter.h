#ifndef OBJ_POINTDEXTER_H
#define OBJ_POINTDEXTER_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitbox;
	uint16 aniFrames;
} ObjectPointdexter;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 timer;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
} EntityPointdexter;

extern ObjectPointdexter* Pointdexter;

void Pointdexter_EnemyInfoHook();

#define OBJ_POINTDEXTER_SETUP \
  REGISTER_ENEMY(Pointdexter)

#endif //! OBJ_POINTDEXTER_H
