#pragma once

extern ObjectBuggernaut* Buggernaut;

void Buggernaut_EnemyInfoHook();

#define OBJ_BUGGERNAUT_SETUP \
  REGISTER_ENEMY(Buggernaut)