#ifndef OBJ_KANABUN_H
#define OBJ_KANABUN_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
} ObjectKanabun;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 unused;
	Vector2 startPos;
	uint8 startDir;
	int32 hVel;
	uint8 hDist;
	uint8 bobDist;
	uint8 angleVel;
	Animator animator;
} EntityKanabun;

extern ObjectKanabun* Kanabun;

void Kanabun_EnemyInfoHook();

#define OBJ_KANABUN_SETUP \
  REGISTER_ENEMY(Kanabun)

#endif //! OBJ_KANABUN_H
