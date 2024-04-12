#pragma once

extern ObjectHatterkiller* Hatterkiller;

void Hatterkiller_EnemyInfoHook();

#define OBJ_HATTERKILLER_SETUP \
  REGISTER_ENEMY(Hatterkiller)