#pragma once

extern ObjectScarab* Scarab;

extern void (*Scarab_HandlePlayerRelease)();

void Scarab_EnemyInfoHook();

#define OBJ_SCARAB_SETUP \
  IMPORT_PUBLIC_FUNC(Scarab_HandlePlayerRelease); \
  REGISTER_ENEMY(Scarab)