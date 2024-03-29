#ifndef OBJ_SOL_H
#define OBJ_SOL_H

#include "GameAPI/Game.h"

#define SOL_FLAMEORB_COUNT (4)

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxOrb;
	uint16 aniFrames;
} ObjectSol;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	uint8 activeOrbs;
	Vector2 positions[SOL_FLAMEORB_COUNT];
	int32 oscillateAngle;
	bool32 isFlameFX;
	bool32 fireOrbs;
	Animator mainAnimator;
	Animator ballAnimator;
} EntitySol;

extern ObjectSol* Sol;

extern void (*Sol_State_Moving)();
extern void (*Sol_State_ShootingOrbs)();
extern void (*Sol_State_NoOrbs)();
extern void (*Sol_State_ActiveFireball)();

void Sol_EnemyInfoHook();

#define OBJ_SOL_SETUP \
  IMPORT_PUBLIC_FUNC(Sol_State_Moving); \
  IMPORT_PUBLIC_FUNC(Sol_State_ShootingOrbs); \
  IMPORT_PUBLIC_FUNC(Sol_State_NoOrbs); \
  IMPORT_PUBLIC_FUNC(Sol_State_ActiveFireball); \
  REGISTER_ENEMY(Sol)

#endif //! OBJ_SOL_H
