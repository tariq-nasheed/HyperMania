#pragma once

extern ObjectTechnosqueek* Technosqueek;

void Technosqueek_EnemyInfoHook();

#define OBJ_TECHNOSQUEEK_SETUP \
  REGISTER_ENEMY(Technosqueek)