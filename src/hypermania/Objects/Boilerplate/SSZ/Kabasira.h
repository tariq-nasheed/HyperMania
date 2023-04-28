#ifndef OBJ_KABASIRA_H
#define OBJ_KABASIRA_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Vector2 onScreenRange;
	uint16 aniFrames;
	uint16 sfxPon;
	uint16 sfxExplosion2;
} ObjectKabasira;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 unused1;
	int32 unused2;
	Vector2 startPos;
	uint8 startDir;
	int32 timer;
	Animator bodyAnimator;
	Animator wingsAnimator;
	int32 unused3;
} EntityKabasira;

extern ObjectKabasira* Kabasira;

extern void (*Kabasira_State_Moving)();

void Kabasira_EnemyInfoHook();

#define OBJ_KABASIRA_SETUP \
  IMPORT_PUBLIC_FUNC(Kabasira_State_Moving); \
  REGISTER_ENEMY(Kabasira)

#endif //! OBJ_KABASIRA_H
