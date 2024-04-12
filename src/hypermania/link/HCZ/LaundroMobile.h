#pragma once

extern ObjectWhirlpool* Whirlpool;
extern ObjectLaundroMobile* LaundroMobile;

extern void (*LaundroMobile_StateBoss_AwaitPlayer_Phase1)();
extern void (*LaundroMobile_StateBoss_SetupArena_Phase1)();
extern void (*LaundroMobile_StateBoss_Destroyed_Phase1)();
extern void (*LaundroMobile_StateBoss_Destroyed_Phase2)();
extern void (*LaundroMobile_StateBoss_Explode_Phase2)();

void LaundroMobile_EnemyInfoHook();

#define OBJ_LAUNDROMOBILE_SETUP \
  MOD_REGISTER_OBJECT_HOOK(Whirlpool); \
  IMPORT_PUBLIC_FUNC(LaundroMobile_StateBoss_AwaitPlayer_Phase1); \
  IMPORT_PUBLIC_FUNC(LaundroMobile_StateBoss_SetupArena_Phase1); \
  IMPORT_PUBLIC_FUNC(LaundroMobile_StateBoss_Destroyed_Phase1); \
  IMPORT_PUBLIC_FUNC(LaundroMobile_StateBoss_Destroyed_Phase2); \
  IMPORT_PUBLIC_FUNC(LaundroMobile_StateBoss_Explode_Phase2); \
  REGISTER_ENEMY(LaundroMobile)