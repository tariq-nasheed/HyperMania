#pragma once

extern ObjectCactula* Cactula;

void Cactula_EnemyInfoHook();

#define OBJ_CACTULA_SETUP \
  REGISTER_ENEMY(Cactula)