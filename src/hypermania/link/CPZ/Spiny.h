#pragma once

extern ObjectSpiny* Spiny;

extern void (*Spiny_State_Shot)();
extern void (*Spiny_State_ShotDisappear)();

void Spiny_EnemyInfoHook();

#define OBJ_SPINY_SETUP \
  IMPORT_PUBLIC_FUNC(Spiny_State_Shot); \
  IMPORT_PUBLIC_FUNC(Spiny_State_ShotDisappear); \
  REGISTER_ENEMY(Spiny)