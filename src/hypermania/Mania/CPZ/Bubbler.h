#ifndef OBJ_BUBBLER_H
#define OBJ_BUBBLER_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
} ObjectBubbler;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int16 timer;
	uint16 spawnTimer;
	Vector2 startPos;
	uint8 startDir;
	Animator bodyHitbox;
	Animator flameAnimator;
} EntityBubbler;

extern ObjectBubbler* Bubbler;

extern void (*Bubbler_StateProjectile_Seed)();
extern void (*Bubbler_StateProjectile_Bubbler)();

void Bubbler_EnemyInfoHook();

#define OBJ_BUBBLER_SETUP \
  IMPORT_PUBLIC_FUNC(Bubbler_StateProjectile_Seed); \
  IMPORT_PUBLIC_FUNC(Bubbler_StateProjectile_Bubbler); \
  REGISTER_ENEMY(Bubbler)

#endif //! OBJ_BUBBLER_H
