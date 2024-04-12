#ifndef OBJ_BUZZBOMBER_LINK_H
#define OBJ_BUZZBOMBER_LINK_H

extern ObjectBuzzBomber* BuzzBomber;

extern void (*BuzzBomber_State_Flying)();
extern void (*BuzzBomber_State_Idle)();
extern void (*BuzzBomber_State_DetectedPlayer)();

void BuzzBomber_EnemyInfoHook();

#define OBJ_BUZZBOMBER_SETUP \
  IMPORT_PUBLIC_FUNC(BuzzBomber_State_Flying); \
  IMPORT_PUBLIC_FUNC(BuzzBomber_State_Idle); \
  IMPORT_PUBLIC_FUNC(BuzzBomber_State_DetectedPlayer); \
  REGISTER_ENEMY(BuzzBomber)

#endif