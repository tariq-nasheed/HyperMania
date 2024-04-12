#pragma once

extern ObjectMegaChopper* MegaChopper;

extern void (*MegaChopper_State_InWater)();
extern void (*MegaChopper_State_OutOfWater)();

void MegaChopper_EnemyInfoHook();

#define OBJ_MEGACHOPPER_SETUP \
  IMPORT_PUBLIC_FUNC(MegaChopper_State_InWater); \
  IMPORT_PUBLIC_FUNC(MegaChopper_State_OutOfWater); \
  REGISTER_ENEMY(MegaChopper)