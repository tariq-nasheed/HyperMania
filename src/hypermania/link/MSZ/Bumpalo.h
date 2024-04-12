#pragma once

extern ObjectBumpalo* Bumpalo;

void Bumpalo_EnemyInfoHook();

#define OBJ_BUMPALO_SETUP \
  REGISTER_ENEMY(Bumpalo)