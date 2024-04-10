#ifndef OBJ_BUMPALO_H
#define OBJ_BUMPALO_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxBumper;
	Hitbox hitboxRange;
	Hitbox hitboxCharge;
	Hitbox hitboxUnused;
	uint16 aniFrames;
	uint16 sfxBumper;
	uint16 sfxHuff;
	uint16 sfxClack;
	uint16 sfxImpact;
} ObjectBumpalo;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	int32 timer;
	bool32 ignoreCliffs;
	bool32 wallCollided;
	Animator badnikAnimator;
	Animator huffAnimator;
	Animator dustAnimator;
} EntityBumpalo;

extern ObjectBumpalo* Bumpalo;

void Bumpalo_EnemyInfoHook();

#define OBJ_BUMPALO_SETUP \
  REGISTER_ENEMY(Bumpalo)

#endif //! OBJ_BUMPALO_H
