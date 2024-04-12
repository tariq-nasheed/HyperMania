#pragma once

extern ObjectDrillerdroid* Drillerdroid;

extern void (*Drillerdroid_State_SetupArena)();
extern void (*Drillerdroid_State_AwaitPlayer)();
extern void (*Drillerdroid_State_FinishDrilling)();
extern void (*Drillerdroid_State_JumpTargeting)();
extern void (*Drillerdroid_State_DecidingDropPos)();
extern void (*Drillerdroid_State_DropFailReset)();
extern void (*Drillerdroid_State_Destroyed)();
extern void (*Drillerdroid_State_Finish)();
extern void (*Drillerdroid_State_DropSignPost)();
extern void (*Drillerdroid_State_Target)();
extern void (*Drillerdroid_Hit)();

void Drillerdroid_EnemyInfoHook();

#define OBJ_DRILLERDROID_SETUP \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_SetupArena); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_AwaitPlayer); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_FinishDrilling); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_JumpTargeting); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_DecidingDropPos); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_DropFailReset); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_Destroyed); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_Finish); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_DropSignPost); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_State_Target); \
  IMPORT_PUBLIC_FUNC(Drillerdroid_Hit); \
  REGISTER_ENEMY(Drillerdroid)