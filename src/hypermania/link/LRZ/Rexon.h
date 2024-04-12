#pragma once

extern ObjectRexon* Rexon;

extern void (*Rexon_State_Hidden)();
extern void (*Rexon_State_Rising)();
extern void (*Rexon_State_Shooting)();
extern void (*Rexon_State_Destroyed)();

void Rexon_EnemyInfoHook();

#define OBJ_REXON_SETUP \
  IMPORT_PUBLIC_FUNC(Rexon_State_Hidden); \
  IMPORT_PUBLIC_FUNC(Rexon_State_Rising); \
  IMPORT_PUBLIC_FUNC(Rexon_State_Shooting); \
  IMPORT_PUBLIC_FUNC(Rexon_State_Destroyed); \
  REGISTER_ENEMY(Rexon)