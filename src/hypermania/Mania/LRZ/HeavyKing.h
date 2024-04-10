#ifndef OBJ_HEAVYKING_H
#define OBJ_HEAVYKING_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	TABLE(int32 attackPattern[32], { 0, 0, 1, 0, 2, 2, 1, 0, 0, 1, 1, 2, 0, 2, 0, 0, 2, 1, 1, 2, 1, 0, 1, 0, 2, 2, 0, 1, 0, 0, 2, 1 });
	int32 attackPatternPos;
	Hitbox hitboxBody;
	Hitbox hitboxBoss;
	Hitbox hitboxCharging;
	int32 boundsL;
	int32 boundsM;
	int32 boundsR;
	int32 spinRaySpawnPos;
	int32 startY;
	uint16 sfxHit;
	uint16 sfxImpact2;
	uint16 sfxImpact5;
	uint16 sfxCharge;
	uint16 sfxExplosion;
	uint16 sfxFreeze;
	uint16 sfxRodPlant;
	uint16 sfxRodShine;
	uint16 sfxElecOn;
	uint16 sfxTwinCharge;
	uint16 sfxImpact6;
	uint16 aniFrames;
	uint16 cutsceneFrames;
} ObjectHeavyKing;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateStore);
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 curAttack;
	int32 attacksRemaining;
	Vector2 originPos;
	Entity* claw;
	Entity* masterEmerald;
	Entity* targetEmerald;
	Animator bodyAnimator;
	Animator scepterAnimator;
	Animator electricityAnimator;
	Animator storedBodyAnimator;
	Animator storedScepterAnimator;
} EntityHeavyKing;

extern ObjectHeavyKing* HeavyKing;

extern void (*HeavyKing_State_JumpToTargetEmerald)();
extern void (*HeavyKing_State_Leaping)();
extern void (*HeavyKing_State_LeapToMasterEmerald)();
extern void (*HeavyKing_State_LandedOnMasterEmerald)();
extern void (*HeavyKing_State_ChargeStart)();
extern void (*HeavyKing_State_ChargeStop)();
extern void (*HeavyKing_State_PrepareHover)();
extern void (*HeavyKing_State_StartHovering)();
extern void (*HeavyKing_State_Hovering)();
extern void (*HeavyKing_State_LaserAttack)();
extern void (*HeavyKing_State_ExpandRingAttack)();
extern void (*HeavyKing_State_TwinChargeAttack)();
extern void (*HeavyKing_Hit)();

void HeavyKing_EnemyInfoHook();

#define OBJ_HEAVYKING_SETUP \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_JumpToTargetEmerald); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_Leaping); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_LeapToMasterEmerald); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_LandedOnMasterEmerald); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_ChargeStart); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_ChargeStop); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_PrepareHover); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_StartHovering); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_Hovering); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_LaserAttack); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_ExpandRingAttack); \
  IMPORT_PUBLIC_FUNC(HeavyKing_State_TwinChargeAttack); \
  IMPORT_PUBLIC_FUNC(HeavyKing_Hit); \
  REGISTER_ENEMY(HeavyKing)

#endif //! OBJ_HEAVYKING_H
