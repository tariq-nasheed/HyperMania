#ifndef OBJ_FIREWORM_H
#define OBJ_FIREWORM_H

#include "GameAPI/Game.h"

#define FIREWORM_SEGMENT_COUNT (1 + 4)

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Animator holeAnimator;
	uint16 aniFrames;
} ObjectFireworm;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	Vector2 bodyPositions[FIREWORM_SEGMENT_COUNT];
	Vector2 bodyVelocities[FIREWORM_SEGMENT_COUNT];
	uint8 bodyDirections[FIREWORM_SEGMENT_COUNT];
	uint16 bodyAngles[FIREWORM_SEGMENT_COUNT];
	uint8 bodyTimers[FIREWORM_SEGMENT_COUNT];
	uint8 flameExhaustDelays[FIREWORM_SEGMENT_COUNT];
	int32 bodyOriginY[FIREWORM_SEGMENT_COUNT];
	int32 timer;
	int32 boundsL;
	int32 boundsR;
	Animator bodyAnimators[FIREWORM_SEGMENT_COUNT];
	Animator flameAnimators[FIREWORM_SEGMENT_COUNT];
} EntityFireworm;

extern ObjectFireworm* Fireworm;

extern void (*Fireworm_State_FlyAround)();

void Fireworm_EnemyInfoHook();

#define OBJ_FIREWORM_SETUP \
  IMPORT_PUBLIC_FUNC(Fireworm_State_FlyAround); \
  REGISTER_ENEMY(Fireworm)

#endif //! OBJ_FIREWORM_H
