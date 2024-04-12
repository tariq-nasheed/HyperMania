#pragma once

extern ObjectAmoebaDroid* AmoebaDroid;

extern void (*AmoebaDroid_State_DropIn)();
extern void (*AmoebaDroid_State_DropIntoPool)();
extern void (*AmoebaDroid_State_SurfaceFromPool)();
extern void (*AmoebaDroid_State_ChooseAttack)();
extern void (*AmoebaDroid_State_ExitPool)();
extern void (*AmoebaDroid_State_BounceAttack)();
extern void (*AmoebaDroid_State_GatherBlobs)();
extern void (*AmoebaDroid_State_SpinBlobs)();
extern void (*AmoebaDroid_Hit)();

void AmoebaDroid_EnemyInfoHook();

#define OBJ_AMOEBADROID_SETUP \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_DropIn); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_DropIntoPool); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_SurfaceFromPool); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_ChooseAttack); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_ExitPool); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_BounceAttack); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_GatherBlobs); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_SpinBlobs); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_Hit); \
  REGISTER_ENEMY(AmoebaDroid)