#pragma once

extern ObjectIceBomba* IceBomba;

extern void (*IceBomba_State_Flying)();
extern void (*IceBomba_State_Turning)();
extern void (*IceBomba_State_FlyAway)();

void IceBomba_EnemyInfoHook();

#define OBJ_ICEBOMBA_SETUP \
  IMPORT_PUBLIC_FUNC(IceBomba_State_Flying); \
  IMPORT_PUBLIC_FUNC(IceBomba_State_Turning); \
  IMPORT_PUBLIC_FUNC(IceBomba_State_FlyAway); \
  REGISTER_ENEMY(IceBomba)