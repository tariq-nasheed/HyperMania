#ifndef OBJ_BATBRAIN_H
#define OBJ_BATBRAIN_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
	uint16 sfxFlap;
} ObjectBatbrain;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 targetY;
	EntityPlayer* target;
	Vector2 startPos;
	Animator animator;
} EntityBatbrain;

extern ObjectBatbrain* Batbrain;

extern void (*Batbrain_State_CheckPlayerInRange)();
extern void (*Batbrain_State_DropToPlayer)();
extern void (*Batbrain_State_Fly)();
extern void (*Batbrain_State_FlyToCeiling)();

void Batbrain_EnemyInfoHook();

#define OBJ_BATBRAIN_SETUP \
  IMPORT_PUBLIC_FUNC(Batbrain_State_CheckPlayerInRange); \
  IMPORT_PUBLIC_FUNC(Batbrain_State_DropToPlayer); \
  IMPORT_PUBLIC_FUNC(Batbrain_State_Fly); \
  IMPORT_PUBLIC_FUNC(Batbrain_State_FlyToCeiling); \
  REGISTER_ENEMY(Batbrain)

#endif //! OBJ_BATBRAIN_H
