#pragma once

extern ObjectClucker* Clucker;

extern void (*Clucker_State_Destroyed)();
extern void (*Clucker_State_Egg)();

void Clucker_EnemyInfoHook();

#define OBJ_CLUCKER_SETUP \
  IMPORT_PUBLIC_FUNC(Clucker_State_Destroyed); \
  IMPORT_PUBLIC_FUNC(Clucker_State_Egg); \
  REGISTER_ENEMY(Clucker)