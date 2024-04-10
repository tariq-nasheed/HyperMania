#ifndef OBJ_AQUIS_H
#define OBJ_AQUIS_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
	uint16 sfxShot;
} ObjectAquis;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	uint8 playerInRange;
	int32 remainingTurns;
	Vector2 startPos;
	uint8 startDir;
	Animator mainAnimator;
	Animator wingAnimator;
} EntityAquis;

extern ObjectAquis* Aquis;

extern void (*Aquis_State_Shot)();

void Aquis_EnemyInfoHook();

#define OBJ_AQUIS_SETUP \
  IMPORT_PUBLIC_FUNC(Aquis_State_Shot); \
  REGISTER_ENEMY(Aquis)

#endif //! OBJ_AQUIS_H
