#pragma once

extern ObjectShiversaw* Shiversaw;

extern void (*Shiversaw_State_Idle)();
extern void (*Shiversaw_State_MoveToPlayer)();
extern void (*Shiversaw_State_HitRecoil)();
extern void (*Shiversaw_Hit)();

void Shiversaw_EnemyInfoHook();

#define OBJ_SHIVERSAW_SETUP \
  IMPORT_PUBLIC_FUNC(Shiversaw_State_Idle); \
  IMPORT_PUBLIC_FUNC(Shiversaw_State_MoveToPlayer); \
  IMPORT_PUBLIC_FUNC(Shiversaw_State_HitRecoil); \
  IMPORT_PUBLIC_FUNC(Shiversaw_Hit); \
  REGISTER_ENEMY(Shiversaw)