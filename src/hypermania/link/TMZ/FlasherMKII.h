#pragma once

extern ObjectFlasherMKII* FlasherMKII;

void FlasherMKII_EnemyInfoHook();

#define OBJ_FLASHERMKII_SETUP \
  REGISTER_ENEMY(FlasherMKII)