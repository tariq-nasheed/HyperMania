#pragma once

extern ObjectWoodrow* Woodrow;

extern void (*Woodrow_State_Idle)();
extern void (*Woodrow_State_MoveUp)();
extern void (*Woodrow_State_MoveDown)();

void Woodrow_EnemyInfoHook();

#define OBJ_WOODROW_SETUP \
  IMPORT_PUBLIC_FUNC(Woodrow_State_Idle); \
  IMPORT_PUBLIC_FUNC(Woodrow_State_MoveUp); \
  IMPORT_PUBLIC_FUNC(Woodrow_State_MoveDown); \
  REGISTER_ENEMY(Woodrow)