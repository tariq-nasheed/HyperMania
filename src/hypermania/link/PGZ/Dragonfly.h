#pragma once

extern ObjectDragonfly* Dragonfly;

extern void (*Dragonfly_State_Move)();

void Dragonfly_EnemyInfoHook();

#define OBJ_DRAGONFLY_SETUP \
  IMPORT_PUBLIC_FUNC(Dragonfly_State_Move); \
  REGISTER_ENEMY(Dragonfly)