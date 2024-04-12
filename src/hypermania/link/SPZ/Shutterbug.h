#pragma once

extern ObjectShutterbug* Shutterbug;

void Shutterbug_EnemyInfoHook();

#define OBJ_SHUTTERBUG_SETUP \
  REGISTER_ENEMY(Shutterbug)