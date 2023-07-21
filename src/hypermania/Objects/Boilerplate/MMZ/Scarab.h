#ifndef OBJ_SCARAB_H
#define OBJ_SCARAB_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxGrab;
	uint16 aniFrames;
} ObjectScarab;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	Vector2 moveOffset;
	uint8 startDir;
	int32 timer;
	int32 playerTimers[PLAYER_COUNT];
	Animator bodyAnimator;
	Animator frontLegAnimator;
	Animator backLegAnimator;
	int32 amplitude;
	uint8 childCount;
	ManiaPlaneFilterTypes planeFilter;
	uint8 drawGroupLow;
	uint8 drawGroupHigh;
	uint8 pullCount;
	int8 moveDir;
	uint8 grabbedPlayers;
} EntityScarab;

extern ObjectScarab* Scarab;

extern void (*Scarab_HandlePlayerRelease)();

void Scarab_EnemyInfoHook();

#define OBJ_SCARAB_SETUP \
  IMPORT_PUBLIC_FUNC(Scarab_HandlePlayerRelease); \
  REGISTER_ENEMY(Scarab)

#endif //! OBJ_SCARAB_H
