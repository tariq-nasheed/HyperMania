#pragma once

extern ObjectNewtron* Newtron;

extern void (*Newtron_State_StartFly)();
extern void (*Newtron_State_Fly)();
extern void (*Newtron_State_Shoot)();

void Newtron_EnemyInfoHook();

#define OBJ_NEWTRON_SETUP \
  IMPORT_PUBLIC_FUNC(Newtron_State_StartFly); \
  IMPORT_PUBLIC_FUNC(Newtron_State_Fly); \
  IMPORT_PUBLIC_FUNC(Newtron_State_Shoot); \
  REGISTER_ENEMY(Newtron)