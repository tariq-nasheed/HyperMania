#pragma once

extern ObjectOctus* Octus;

extern void (*Octus_State_Shot)();

void Octus_EnemyInfoHook();

#define OBJ_OCTUS_SETUP \
  IMPORT_PUBLIC_FUNC(Octus_State_Shot); \
  REGISTER_ENEMY(Octus)