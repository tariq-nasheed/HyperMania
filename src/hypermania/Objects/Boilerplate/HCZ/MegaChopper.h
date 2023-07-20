#ifndef OBJ_MEGACHOPPER_H
#define OBJ_MEGACHOPPER_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxChop;
	uint16 aniFrames;
} ObjectMegaChopper;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	EntityPlayer* grabbedPlayer;
	Vector2 playerPos;
	uint8 playerDir;
	uint16 shakeTimer;
	uint16 shakeCount;
	uint16 lastShakeFlags;
	uint8 nibbleTimer;
	Animator animator;
} EntityMegaChopper;

extern ObjectMegaChopper* MegaChopper;

extern void (*MegaChopper_State_InWater)();
extern void (*MegaChopper_State_OutOfWater)();

void MegaChopper_EnemyInfoHook();

#define OBJ_MEGACHOPPER_SETUP \
  IMPORT_PUBLIC_FUNC(MegaChopper_State_InWater); \
  IMPORT_PUBLIC_FUNC(MegaChopper_State_OutOfWater); \
  REGISTER_ENEMY(MegaChopper)

#endif //! OBJ_MEGACHOPPER_H
