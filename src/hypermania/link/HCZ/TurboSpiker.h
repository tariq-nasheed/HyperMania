#pragma once

extern ObjectTurboSpiker* TurboSpiker;

extern void (*TurboSpiker_State_Spike)();
extern void (*TurboSpiker_State_Ember)();

void TurboSpiker_EnemyInfoHook();

#define OBJ_TURBOSPIKER_SETUP \
  IMPORT_PUBLIC_FUNC(TurboSpiker_State_Spike); \
  IMPORT_PUBLIC_FUNC(TurboSpiker_State_Ember); \
  REGISTER_ENEMY(TurboSpiker)