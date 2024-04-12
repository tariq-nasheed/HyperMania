#pragma once

extern ObjectMicDrop* MicDrop;

void MicDrop_EnemyInfoHook();

#define OBJ_MICDROP_SETUP \
  REGISTER_ENEMY(MicDrop)
