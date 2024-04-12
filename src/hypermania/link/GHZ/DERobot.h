#pragma once

extern ObjectDERobot* DERobot;

extern void (*DERobot_State_FallLand)();
extern void (*DERobot_State_Walk)();
extern void (*DERobot_State_ArmAttack)();
extern void (*DERobot_Hit)();

void DERobot_EnemyInfoHook();

#define OBJ_DEROBOT_SETUP \
  IMPORT_PUBLIC_FUNC(DERobot_State_FallLand); \
  IMPORT_PUBLIC_FUNC(DERobot_State_Walk); \
  IMPORT_PUBLIC_FUNC(DERobot_State_ArmAttack); \
  IMPORT_PUBLIC_FUNC(DERobot_Hit); \
  REGISTER_ENEMY(DERobot)
