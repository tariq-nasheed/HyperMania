#pragma once

extern ObjectArmadiloid* Armadiloid;

void Armadiloid_EnemyInfoHook();
extern void (*Armadiloid_State_Rider)();

#define OBJ_ARMADILOID_SETUP \
  IMPORT_PUBLIC_FUNC(Armadiloid_State_Rider); \
  REGISTER_ENEMY(Armadiloid)