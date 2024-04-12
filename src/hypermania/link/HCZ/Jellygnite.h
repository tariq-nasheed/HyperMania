#pragma once

extern ObjectJellygnite* Jellygnite;

extern void (*Jellygnite_State_Init)();

void Jellygnite_EnemyInfoHook();

#define OBJ_JELLYGNITE_SETUP \
  IMPORT_PUBLIC_FUNC(Jellygnite_State_Init); \
  REGISTER_ENEMY(Jellygnite)