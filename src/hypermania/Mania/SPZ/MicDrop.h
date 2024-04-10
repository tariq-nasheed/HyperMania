#ifndef OBJ_MICDROP_H
#define OBJ_MICDROP_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxElectrify;
} ObjectMicDrop;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Animator bodyAnimator;
	Animator wireAnimator;
	Vector2 startPos;
	uint16 distance;
	int32 timer;
	int32 swingSpeed;
	int32 swingVel;
	int32 radius;
	int32 swingPos;
} EntityMicDrop;

extern ObjectMicDrop* MicDrop;

void MicDrop_EnemyInfoHook();

#define OBJ_MICDROP_SETUP \
  REGISTER_ENEMY(MicDrop)

#endif //! OBJ_MICDROP_H
