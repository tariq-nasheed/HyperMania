#pragma once

extern ObjectRattlekiller* Rattlekiller;

void Rattlekiller_EnemyInfoHook();

#define OBJ_RATTLEKILLER_SETUP \
  REGISTER_ENEMY(Rattlekiller)