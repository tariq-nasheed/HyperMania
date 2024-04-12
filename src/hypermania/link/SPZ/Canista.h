#pragma once

extern ObjectCanista* Canista;

extern void (*Canista_State_Moving)();
extern void (*Canista_State_Idle)();

void Canista_EnemyInfoHook();

#define OBJ_CANISTA_SETUP \
  IMPORT_PUBLIC_FUNC(Canista_State_Moving); \
  IMPORT_PUBLIC_FUNC(Canista_State_Idle); \
  REGISTER_ENEMY(Canista)