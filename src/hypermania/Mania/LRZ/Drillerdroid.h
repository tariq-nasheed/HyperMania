#ifndef OBJ_DRILLERDROID_H
#define OBJ_DRILLERDROID_H

#include "GameAPI/Game.h"

typedef enum {
	DRILLERDROID_MAIN,
	DRILLERDROID_TARGET,
	DRILLERDROID_UNUSED,
} DrillerdroidTypes;

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxCore;
	Hitbox hitboxPistonL;
	Hitbox hitboxPistonR;
	Hitbox hitboxDrillL;
	Hitbox hitboxDrillR;
	int32 pistonPos[2];
	int32 drillPos[2];
	int32 pistonDelay[2];
	int32 drillDelay[2];
	int32 pistonMoveDir[2];
	int32 drillMoveDir[2];
	uint8 platformActive[5];
	uint8 arenaSegment;
	uint8 playerTimers[PLAYER_COUNT];
	uint8 drillSfxTimer;
	bool32 playingDrillSfx;
	uint8 armorHealth;
	uint8 jumpsRemaining;
	uint8 canBreakSegment;
	int32 stalatiteOffset;
	Entity* boss;
	uint16 aniFrames;
	uint16 ticFrames;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxDrill;
	uint16 sfxImpact;
	uint16 sfxJump;
	uint16 sfxTargeting;
	uint16 sfxSizzle;
	uint16 sfxDrop;
	uint16 sfxFail;
	uint16 sfxClang;
} ObjectDrillerdroid;

typedef struct {
	RSDK_ENTITY
	uint8 type;
	StateMachine(state);
	StateMachine(stateDraw);
	Animator mainAnimator;
	Animator armorAnimator;
	Animator targetLockAnimator;
	EntityPlayer* target;
	Vector2 targetEdgeOffset;
	int32 startY;
	int32 timer;
	uint8 invincibilityTimer;
	int8 health;
} EntityDrillerdroid;

extern ObjectDrillerdroid* Drillerdroid;

extern void (*Drillerdroid_State_SetupArena)();
extern void (*Drillerdroid_State_AwaitPlayer)();
extern void (*Drillerdroid_State_FinishDrilling)();
extern void (*Drillerdroid_State_JumpTargeting)();
extern void (*Drillerdroid_State_DecidingDropPos)();
extern void (*Drillerdroid_State_DropFailReset)();
extern void (*Drillerdroid_State_Destroyed)();
extern void (*Drillerdroid_State_Finish)();
extern void (*Drillerdroid_State_DropSignPost)();
extern void (*Drillerdroid_State_Target)();
extern void (*Drillerdroid_Hit)();

void Drillerdroid_EnemyInfoHook();

#define OBJ_DRILLERDROID_SETUP \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_SetupArena); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_AwaitPlayer); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_FinishDrilling); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_JumpTargeting); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_DecidingDropPos); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_DropFailReset); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_Destroyed); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_Finish); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_DropSignPost); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_Target); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_Hit); \
  REGISTER_ENEMY(Drillerdroid)

#endif //! OBJ_DRILLERDROID_H
