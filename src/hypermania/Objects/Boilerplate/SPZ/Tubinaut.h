#ifndef OBJ_TUBINAUT_H
#define OBJ_TUBINAUT_H

#include "GameAPI/Game.h"

#define TUBINAUT_ORB_COUNT (3)

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxFace;
	Hitbox hitboxOrb;
	Hitbox hitboxSpin;
	uint16 aniFrames;
	uint16 sfxPowerdown;
	uint16 sfxRepel;
} ObjectTubinaut;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(orbState);
	Animator bodyAnimator;
	Animator fieldAnimator;
	Vector2 startPos;
	Vector2 orbPositions[TUBINAUT_ORB_COUNT];
	int32 orbAngles[TUBINAUT_ORB_COUNT];
	int16 reAdjustTimers[TUBINAUT_ORB_COUNT];
	bool32 ballsVisible[TUBINAUT_ORB_COUNT]; // hehe
	Animator ballAnimators[TUBINAUT_ORB_COUNT];
	uint16 playerTimers[PLAYER_COUNT];
	int32 attackTimer;
	uint16 activeOrbs;
	uint8 orbCount;
	int32 timer;
	uint16 distanceRemain;
	uint16 distance;
} EntityTubinaut;

extern ObjectTubinaut* Tubinaut;

extern void (*Tubinaut_State_Move)();

void Tubinaut_EnemyInfoHook();

#define OBJ_TUBINAUT_SETUP \
  IMPORT_PUBLIC_FUNC(Tubinaut_State_Move); \
  REGISTER_ENEMY(Tubinaut)

#endif //! OBJ_TUBINAUT_H
