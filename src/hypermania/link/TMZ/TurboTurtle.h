#pragma once

extern ObjectTurboTurtle* TurboTurtle;

void TurboTurtle_EnemyInfoHook();

#define OBJ_TURBOTURTLE_SETUP \
  REGISTER_ENEMY(TurboTurtle)