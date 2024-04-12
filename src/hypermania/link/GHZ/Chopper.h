#ifndef OBJ_CHOPPER_LINK_H
#define OBJ_CHOPPER_LINK_H

extern ObjectChopper* Chopper;

extern void (*Chopper_State_Jump)();

void Chopper_EnemyInfoHook();

#define OBJ_CHOPPER_SETUP \
  IMPORT_PUBLIC_FUNC(Chopper_State_Jump); \
  REGISTER_ENEMY(Chopper)

#endif