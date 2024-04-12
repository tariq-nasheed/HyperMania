#pragma once

extern ObjectKanabun* Kanabun;

void Kanabun_EnemyInfoHook();

#define OBJ_KANABUN_SETUP \
  REGISTER_ENEMY(Kanabun)