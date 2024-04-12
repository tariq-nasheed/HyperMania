#pragma once

extern ObjectSol* Sol;

extern void (*Sol_State_Moving)();
extern void (*Sol_State_ShootingOrbs)();
extern void (*Sol_State_NoOrbs)();
extern void (*Sol_State_ActiveFireball)();

void Sol_EnemyInfoHook();

#define OBJ_SOL_SETUP \
  IMPORT_PUBLIC_FUNC(Sol_State_Moving); \
  IMPORT_PUBLIC_FUNC(Sol_State_ShootingOrbs); \
  IMPORT_PUBLIC_FUNC(Sol_State_NoOrbs); \
  IMPORT_PUBLIC_FUNC(Sol_State_ActiveFireball); \
  REGISTER_ENEMY(Sol)
