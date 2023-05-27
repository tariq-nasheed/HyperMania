#ifndef OBJ_NEWTRON_H
#define OBJ_NEWTRON_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxShoot;
	Hitbox hitboxFly;
	Hitbox hitboxProjectile;
	Hitbox hitboxRange;
	uint16 aniFrames;
} ObjectNewtron;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	int32 timer;
	Vector2 startPos;
	Animator animator;
	Animator flameAnimator;
} EntityNewtron;

extern ObjectNewtron* Newtron;

extern void (*Newtron_State_StartFly)();
extern void (*Newtron_State_Fly)();
extern void (*Newtron_State_Shoot)();

void Newtron_EnemyInfoHook();

#define OBJ_NEWTRON_SETUP \
  IMPORT_PUBLIC_FUNC(Newtron_State_StartFly); \
  IMPORT_PUBLIC_FUNC(Newtron_State_Fly); \
  IMPORT_PUBLIC_FUNC(Newtron_State_Shoot); \
  REGISTER_ENEMY(Newtron)

#endif //! OBJ_NEWTRON_H
