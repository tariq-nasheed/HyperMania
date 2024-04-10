#ifndef OBJ_ROCKDRILL_H
#define OBJ_ROCKDRILL_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBody;
	Hitbox hitboxPistonL;
	Hitbox hitboxPistonR;
	Hitbox hitboxDrills;
	uint8 drillSfxTimer;
	bool32 playingDrillSfx;
	uint16 aniFrames;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxDrill;
} ObjectRockDrill;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Animator animator;
	bool32 lockCamera;
	int32 boundsL;
	int32 boundsR;
	int32 boundsT;
	int32 boundsB;
	int32 timer;
	int32 pistonPos[2];
	int32 drillPos[2];
	int32 pistonDelay[2];
	int32 drillDelay[2];
	int32 pistonMoveDir[2];
	int32 drillMoveDir[2];
	uint8 invincibilityTimer;
} EntityRockDrill;

extern ObjectRockDrill* RockDrill;

extern void (*RockDrill_State_Drilling)();

void RockDrill_EnemyInfoHook();

#define OBJ_ROCKDRILL_SETUP \
  IMPORT_PUBLIC_FUNC(RockDrill_State_Drilling); \
  REGISTER_ENEMY(RockDrill)

#endif //! OBJ_ROCKDRILL_H
