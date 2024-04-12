#pragma once

extern ObjectTubinaut* Tubinaut;

extern void (*Tubinaut_State_Move)();

void Tubinaut_EnemyInfoHook();

#define OBJ_TUBINAUT_SETUP \
  IMPORT_PUBLIC_FUNC(Tubinaut_State_Move); \
  REGISTER_ENEMY(Tubinaut)