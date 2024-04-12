#pragma once

extern ObjectPohBee* PohBee;

void PohBee_EnemyInfoHook();

#define OBJ_POHBEE_SETUP \
  REGISTER_ENEMY(PohBee)