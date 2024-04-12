#pragma once

extern ObjectVultron* Vultron;

void Vultron_EnemyInfoHook();

#define OBJ_VULTRON_SETUP \
  REGISTER_ENEMY(Vultron)
