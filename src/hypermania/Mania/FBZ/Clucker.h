
#ifndef OBJ_CLUCKER_H
#define OBJ_CLUCKER_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxSolid;
	Hitbox hitboxEgg;
	uint16 aniFrames;
	uint16 sfxShot;
} ObjectClucker;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 yOffset;
	int32 xOffset;
	uint8 timer;
	uint16 delay;
	bool32 hasParent;
	Animator animator;
} EntityClucker;

extern ObjectClucker* Clucker;

extern void (*Clucker_State_Destroyed)();
extern void (*Clucker_State_Egg)();

void Clucker_EnemyInfoHook();

#define OBJ_CLUCKER_SETUP \
  IMPORT_PUBLIC_FUNC(Clucker_State_Destroyed); \
  IMPORT_PUBLIC_FUNC(Clucker_State_Egg); \
  REGISTER_ENEMY(Clucker)

#endif //! OBJ_CLUCKER_H
