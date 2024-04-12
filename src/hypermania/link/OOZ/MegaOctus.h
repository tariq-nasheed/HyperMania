#pragma once

extern ObjectMegaOctus* MegaOctus;

extern void (*MegaOctus_State_EnterMegaOctus)();
extern void (*MegaOctus_State_OpenHatchAndLaugh)();
extern void (*MegaOctus_State_CloseHatch)();
extern void (*MegaOctus_State_DiveIntoOil)();
extern void (*MegaOctus_State_SpawnWeapons)();
extern void (*MegaOctus_State_CannonThenSpawnOrbs)();
extern void (*MegaOctus_StateOrb_Wait)();
extern void (*MegaOctus_StateOrb_FireShot)();
extern void (*MegaOctus_StateOrb_Idle)();
extern void (*MegaOctus_StateOrb_Destroyed)();
extern void (*MegaOctus_Hit)();

void MegaOctus_EnemyInfoHook();

#define OBJ_MEGAOCTUS_SETUP \
  IMPORT_PUBLIC_FUNC(MegaOctus_Hit); \
  IMPORT_PUBLIC_FUNC(MegaOctus_State_OpenHatchAndLaugh); \
  IMPORT_PUBLIC_FUNC(MegaOctus_State_CloseHatch); \
  IMPORT_PUBLIC_FUNC(MegaOctus_State_DiveIntoOil); \
  IMPORT_PUBLIC_FUNC(MegaOctus_State_SpawnWeapons); \
  IMPORT_PUBLIC_FUNC(MegaOctus_State_CannonThenSpawnOrbs); \
  IMPORT_PUBLIC_FUNC(MegaOctus_StateOrb_Wait); \
  IMPORT_PUBLIC_FUNC(MegaOctus_StateOrb_FireShot); \
  IMPORT_PUBLIC_FUNC(MegaOctus_StateOrb_Idle); \
  IMPORT_PUBLIC_FUNC(MegaOctus_StateOrb_Destroyed); \
  REGISTER_ENEMY(MegaOctus)