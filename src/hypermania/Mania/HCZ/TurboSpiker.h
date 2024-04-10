#ifndef OBJ_TURBOSPIKER_H
#define OBJ_TURBOSPIKER_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxSpike;
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxLaunch;
	uint16 sfxSplash;
} ObjectTurboSpiker;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint32 type;
	int32 timer;
	int32 unused;
	Vector2 startPos;
	uint8 startDir;
	Entity* spike;
	Animator shellAnimator;
	Animator animator;
	bool32 playedLaunchSfx;
} EntityTurboSpiker;

extern ObjectTurboSpiker* TurboSpiker;

extern void (*TurboSpiker_State_Spike)();
extern void (*TurboSpiker_State_Ember)();

void TurboSpiker_EnemyInfoHook();

#define OBJ_TURBOSPIKER_SETUP \
  IMPORT_PUBLIC_FUNC(TurboSpiker_State_Spike); \
  IMPORT_PUBLIC_FUNC(TurboSpiker_State_Ember); \
  REGISTER_ENEMY(TurboSpiker)

#endif //! OBJ_TURBOSPIKER_H
