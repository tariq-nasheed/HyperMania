#pragma once

extern ObjectRollerMKII* RollerMKII;

extern void (*RollerMKII_State_Idle)();
extern void (*RollerMKII_State_SpinUp)();

void RollerMKII_EnemyInfoHook();

#define OBJ_ROLLERMKII_SETUP \
  IMPORT_PUBLIC_FUNC(RollerMKII_State_Idle); \
  IMPORT_PUBLIC_FUNC(RollerMKII_State_SpinUp); \
  REGISTER_ENEMY(RollerMKII)