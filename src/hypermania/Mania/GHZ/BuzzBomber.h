#ifndef OBJ_BUZZBOMBER_H
#define OBJ_BUZZBOMBER_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
} ObjectBuzzBomber;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 shotRange;
	int32 timer;
	uint8 detectedPlayer;
	Vector2 startPos;
	uint8 startDir;
	Entity *projectile;
	Animator animator;
	Animator wingAnimator;
	Animator thrustAnimator;
	Hitbox hitboxRange;
} EntityBuzzBomber;

extern ObjectBuzzBomber* BuzzBomber;

extern void (*BuzzBomber_State_Flying)();
extern void (*BuzzBomber_State_Idle)();
extern void (*BuzzBomber_State_DetectedPlayer)();

void BuzzBomber_EnemyInfoHook();

#define OBJ_BUZZBOMBER_SETUP \
  IMPORT_PUBLIC_FUNC(BuzzBomber_State_Flying); \
  IMPORT_PUBLIC_FUNC(BuzzBomber_State_Idle); \
  IMPORT_PUBLIC_FUNC(BuzzBomber_State_DetectedPlayer); \
  REGISTER_ENEMY(BuzzBomber)

#endif //! OBJ_BUZZBOMBER_H
