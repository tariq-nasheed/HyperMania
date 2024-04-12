#pragma once

extern ObjectMechaBu* MechaBu;

extern void (*MechaBu_State_Moving)();
extern void (*MechaBu_State_Stopped)();
extern void (*MechaBu_State_Falling)();

void MechaBu_EnemyInfoHook();

#define OBJ_MECHABU_SETUP \
  IMPORT_PUBLIC_FUNC(MechaBu_State_Moving); \
  IMPORT_PUBLIC_FUNC(MechaBu_State_Stopped); \
  IMPORT_PUBLIC_FUNC(MechaBu_State_Falling); \
  REGISTER_ENEMY(MechaBu)