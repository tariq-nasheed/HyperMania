#ifndef OBJ_VULTRON_H
#define OBJ_VULTRON_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxVultron;
} ObjectVultron;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	Vector2 startPos;
	uint8 startDir;
	uint16 dist;
	uint16 distRemain;
	int32 storeY;
	Hitbox hitboxBadnik;
	Animator bodyAnimator;
	Animator flameAnimator;
} EntityVultron;

extern ObjectVultron* Vultron;

void Vultron_EnemyInfoHook();

#define OBJ_VULTRON_SETUP \
  REGISTER_ENEMY(Vultron)

#endif //! OBJ_VULTRON_H
