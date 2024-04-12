#pragma once

extern ObjectAquis* Aquis;

extern void (*Aquis_State_Shot)();

void Aquis_EnemyInfoHook();

#define OBJ_AQUIS_SETUP \
  IMPORT_PUBLIC_FUNC(Aquis_State_Shot); \
  REGISTER_ENEMY(Aquis)
