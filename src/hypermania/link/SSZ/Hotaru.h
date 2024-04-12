#pragma once

extern ObjectHotaru* Hotaru;

void Hotaru_EnemyInfoHook();

#define OBJ_HOTARU_SETUP \
  REGISTER_ENEMY(Hotaru)