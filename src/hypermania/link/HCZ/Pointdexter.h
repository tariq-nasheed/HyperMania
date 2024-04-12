#pragma once

extern ObjectPointdexter* Pointdexter;

void Pointdexter_EnemyInfoHook();

#define OBJ_POINTDEXTER_SETUP \
  REGISTER_ENEMY(Pointdexter)