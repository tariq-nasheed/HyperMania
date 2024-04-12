#pragma once

extern ObjectDango* Dango;

extern void (*Dango_State_Walking)();
extern void (*Dango_State_Turning)();
extern void (*Dango_State_Falling_Uncurled)();
extern void (*Dango_State_Curling)();
extern void (*Dango_State_Rolling)();
extern void (*Dango_State_Falling_Curled)();
extern void (*Dango_State_Uncurling)();

void Dango_EnemyInfoHook();

#define OBJ_DANGO_SETUP \
  IMPORT_PUBLIC_FUNC(Dango_State_Walking); \
  IMPORT_PUBLIC_FUNC(Dango_State_Turning); \
  IMPORT_PUBLIC_FUNC(Dango_State_Falling_Uncurled); \
  IMPORT_PUBLIC_FUNC(Dango_State_Curling); \
  IMPORT_PUBLIC_FUNC(Dango_State_Rolling); \
  IMPORT_PUBLIC_FUNC(Dango_State_Falling_Curled); \
  IMPORT_PUBLIC_FUNC(Dango_State_Uncurling); \
  REGISTER_ENEMY(Dango)