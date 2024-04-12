#pragma once

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