#ifndef OBJ_TECHNOSQUEEK_H
#define OBJ_TECHNOSQUEEK_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
} ObjectTechnosqueek;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	uint8 speed;
	uint16 distance;
	uint8 distRemain;
	int32 acceleration;
	int32 targetVel;
	int32 tailOffset;
	bool32 shouldTurn;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
	Animator tailAnimator;
} EntityTechnosqueek;

extern ObjectTechnosqueek* Technosqueek;

void Technosqueek_EnemyInfoHook();

#define OBJ_TECHNOSQUEEK_SETUP \
  REGISTER_ENEMY(Technosqueek)

#endif //! OBJ_TECHNOSQUEEK_H
