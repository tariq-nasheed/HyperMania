#ifndef OBJ_SHUTTERBUG_H
#define OBJ_SHUTTERBUG_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxAchievement;
	uint32 pictureCount;
	uint16 aniFrames;
	uint16 snapSfx;
} ObjectShutterbug;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 snaps;
	bool32 passThrough;
	int32 snapTimer;
	uint32 numSnaps;
	EntityPlayer* focusTarget;
	Vector2 startPos;
	Vector2 range;
	Vector2 targetPos;
	uint8 turnTimer;
	uint8 moveDir;
	uint8 flickerTimer;
	Hitbox hitboxRange;
	Animator animator;
	Animator overlayAnimator;
} EntityShutterbug;

extern ObjectShutterbug* Shutterbug;

void Shutterbug_EnemyInfoHook();

#define OBJ_SHUTTERBUG_SETUP \
  REGISTER_ENEMY(Shutterbug)

#endif //! OBJ_SHUTTERBUG_H
