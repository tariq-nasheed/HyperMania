#pragma once

extern ObjectMeterDroid* MeterDroid;

extern void (*MeterDroid_State_TurningValve)();
extern void (*MeterDroid_State_StopTurningValve)();
extern void (*MeterDroid_State_WatchPlatformsPopUp)();
extern void (*MeterDroid_State_Destroyed)();
extern void (*MeterDroid_State_FinishAct)();
extern void (*MeterDroid_Hit)();

void MeterDroid_EnemyInfoHook();

#define OBJ_METERDROID_SETUP \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_TurningValve); \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_StopTurningValve); \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_WatchPlatformsPopUp); \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_Destroyed); \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_FinishAct); \
  IMPORT_PUBLIC_FUNC(MeterDroid_Hit); \
  REGISTER_ENEMY(MeterDroid)