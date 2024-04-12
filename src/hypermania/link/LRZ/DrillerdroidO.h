#pragma once

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