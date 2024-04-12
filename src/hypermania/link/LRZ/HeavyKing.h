#pragma once

extern ObjectHeavyRider* HeavyRider;

extern void (*HeavyRider_State_Moving)();
extern void (*HeavyRider_State_Turning)();
extern void (*HeavyRider_Hit)();

void HeavyRider_EnemyInfoHook();

#define OBJ_HEAVYRIDER_SETUP \
  IMPORT_PUBLIC_FUNC(HeavyRider_State_Moving); \
  IMPORT_PUBLIC_FUNC(HeavyRider_State_Turning); \
  IMPORT_PUBLIC_FUNC(HeavyRider_Hit); \
  REGISTER_ENEMY(HeavyRider)