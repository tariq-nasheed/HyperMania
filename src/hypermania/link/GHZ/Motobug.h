#ifndef OBJ_MOTOBUG_LINK_H
#define OBJ_MOTOBUG_LINK_H

extern ObjectMotobug* Motobug;

extern void (*Motobug_State_Smoke)();

void Motobug_EnemyInfoHook();

#define OBJ_MOTOBUG_SETUP \
  IMPORT_PUBLIC_FUNC(Motobug_State_Smoke); \
  REGISTER_ENEMY(Motobug)
  
#endif