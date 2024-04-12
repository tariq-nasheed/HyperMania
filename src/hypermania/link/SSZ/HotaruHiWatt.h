#pragma once

extern ObjectHotaruHiWatt* HotaruHiWatt;

extern void (*HotaruHiWatt_StateBoss_Appear)();
extern void (*HotaruHiWatt_StateBoss_FlyUp)();
extern void (*HotaruHiWatt_StateBoss_LaserAttackDelay)();
extern void (*HotaruHiWatt_StateBoss_ChargingLaser)();
extern void (*HotaruHiWatt_StateBoss_FinishedLaserAttack)();
extern void (*HotaruHiWatt_StateBoss_LaserAttack_Left)();
extern void (*HotaruHiWatt_StateBoss_LaserAttack_Right)();
extern void (*HotaruHiWatt_StateHotaru_Charging)();
extern void (*HotaruHiWatt_StateHotaru_Attacking)();
extern void (*HotaruHiWatt_StateHotaru_FinishedAttack)();
extern void (*HotaruHiWatt_StateHotaru_EndAttackSequence)();
extern void (*HotaruHiWatt_StateHotaruPair_AttackMovingDown)();
extern void (*HotaruHiWatt_StateHotaruPair_AttackMovingUp)();
extern void (*HotaruHiWatt_SetupHHWReappear)();
extern void (*HotaruHiWatt_SpawnPairHotarus)();
extern void (*HotaruHiWatt_Hit)();

void HotaruHiWatt_EnemyInfoHook();

#define OBJ_HOTARUHIWATT_SETUP \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateBoss_Appear); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateBoss_FlyUp); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateBoss_LaserAttackDelay); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateBoss_LaserAttack_Left); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateBoss_LaserAttack_Right); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateBoss_ChargingLaser); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateBoss_FinishedLaserAttack); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateHotaru_Charging); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateHotaru_Attacking); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateHotaru_FinishedAttack); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateHotaru_EndAttackSequence); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateHotaruPair_AttackMovingDown); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_StateHotaruPair_AttackMovingUp); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_SetupHHWReappear); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_SpawnPairHotarus); \
  IMPORT_PUBLIC_FUNC(HotaruHiWatt_Hit); \
  REGISTER_ENEMY(HotaruHiWatt)