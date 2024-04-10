#ifndef OBJ_DRILLERDROIDO_H
#define OBJ_DRILLERDROIDO_H

#include "GameAPI/Game.h"

typedef enum {
	DRILLERDROIDO_MAIN,
	DRILLERDROIDO_FIREBALLEMITTER,
	DRILLERDROIDO_TARGET,
	DRILLERDROIDO_UNUSED1,
	DRILLERDROIDO_UNUSED2,
} DrillerdroidOTypes;

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxCore;
	Hitbox hitboxPistonL;
	Hitbox hitboxPistonR;
	Hitbox hitboxDrillL;
	Hitbox hitboxDrillR;
	Hitbox hitboxLandPosSegmentBreak;
	Hitbox hitboxLandPosR;
	Hitbox hitboxLandPosL;
	Hitbox hitboxEmitterRange;
	int32 pistonPos[2];
	int32 drillPos[2];
	int32 pistonDelay[2];
	int32 drillDelay[2];
	int32 pistonMoveDir[2];
	int32 drillMoveDir[2];
	uint8 drillSfxTimer;
	bool32 playingDrillSfx;
	uint8 canBreakSegment;
	int32 childSlotStart;
	uint8 currentLevel;
	bool32 emitFireballs;
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
} ObjectDrillerdroidO;

// Entity Class
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
} EntityDrillerdroidO;

extern ObjectDrillerdroidO* DrillerdroidO;

extern void (*DrillerdroidO_State_Dropping)();
extern void (*DrillerdroidO_State_Landed)();
extern void (*DrillerdroidO_State_LandRecoil)();
extern void (*DrillerdroidO_State_BeginDrilling)();
extern void (*DrillerdroidO_State_Drilling)();
extern void (*DrillerdroidO_State_FinishDrilling)();
extern void (*DrillerdroidO_State_Overheat)();
extern void (*DrillerdroidO_State_OverheatRecoil)();
extern void (*DrillerdroidO_State_JumpTargetDelay)();
extern void (*DrillerdroidO_State_OverheatRecoil_DestroyedSegment)();
extern void (*DrillerdroidO_State_Cooldown)();
extern void (*DrillerdroidO_State_ResetFromCooldown)();
extern void (*DrillerdroidO_State_Destroyed)();

void DrillerdroidO_EnemyInfoHook();

#define OBJ_DRILLERDROIDO_SETUP \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_Dropping); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_Landed); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_LandRecoil); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_BeginDrilling); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_Drilling); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_FinishDrilling); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_Overheat); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_OverheatRecoil); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_JumpTargetDelay); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_OverheatRecoil_DestroyedSegment); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_Cooldown); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_ResetFromCooldown); \
  IMPORT_PUBLIC_FUNC(DrillerdroidO_State_Destroyed); \
  REGISTER_ENEMY(DrillerdroidO)

#endif //! OBJ_DRILLERDROIDO_H
