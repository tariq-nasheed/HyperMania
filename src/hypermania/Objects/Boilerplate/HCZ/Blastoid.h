#ifndef OBJ_BLASTOID_H
#define OBJ_BLASTOID_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBody;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
	uint16 sfxShot;
} ObjectBlastoid;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 timer;
	Animator animator;
} EntityBlastoid;

extern ObjectBlastoid* Blastoid;

extern void (*Blastoid_State_Projectile)();

void Blastoid_EnemyInfoHook();

#define OBJ_BLASTOID_SETUP \
  IMPORT_PUBLIC_FUNC(Blastoid_State_Projectile); \
  REGISTER_ENEMY(Blastoid)

#endif //! OBJ_BLASTOID_H
