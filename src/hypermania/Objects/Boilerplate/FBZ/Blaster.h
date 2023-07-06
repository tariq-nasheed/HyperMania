#ifndef OBJ_BLASTER_H
#define OBJ_BLASTER_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
} ObjectBlaster;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint16 unused1;
	uint16 timer;
	uint16 attackTimer;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
} EntityBlaster;

extern ObjectBlaster* Blaster;

extern void (*Blaster_State_BeginShot)();
extern void (*Blaster_State_Shot)();
extern void (*Blaster_State_Shell)();

void Blaster_EnemyInfoHook();

#define OBJ_BLASTER_SETUP \
  IMPORT_PUBLIC_FUNC(Blaster_State_BeginShot); \
  IMPORT_PUBLIC_FUNC(Blaster_State_Shot); \
  IMPORT_PUBLIC_FUNC(Blaster_State_Shell); \
  REGISTER_ENEMY(Blaster)

#endif //! OBJ_BLASTER_H
