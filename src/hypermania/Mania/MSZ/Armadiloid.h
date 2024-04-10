#ifndef OBJ_ARMADILOID_H
#define OBJ_ARMADILOID_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
	uint16 sfxShot;
} ObjectArmadiloid;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 type;
	int32 timer;
	Entity* child;
	Entity* parent;
	Vector2 startPos;
	Hitbox hitbox;
	Animator bodyAnimator;
	Animator headAnimator;
	Animator boosterAnimator;
} EntityArmadiloid;

extern ObjectArmadiloid* Armadiloid;

void Armadiloid_EnemyInfoHook();
extern void (*Armadiloid_State_Rider)();

#define OBJ_ARMADILOID_SETUP \
  IMPORT_PUBLIC_FUNC(Armadiloid_State_Rider); \
  REGISTER_ENEMY(Armadiloid)

#endif //! OBJ_ARMADILOID_H
