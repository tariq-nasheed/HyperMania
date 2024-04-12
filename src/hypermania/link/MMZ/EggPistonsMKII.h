#pragma once

extern ObjectEggPistonsMKII* EggPistonsMKII;

extern void (*EggPistonsMKII_State_ClassicMode)();
extern void (*EggPistonsMKII_State_PinchMode)();
extern void (*EggPistonsMKII_State_Destroyed)();
extern void (*EggPistonsMKII_Hit)();

void EggPistonsMKII_EnemyInfoHook();

#define OBJ_EGGPISTONSMKII_SETUP \
  IMPORT_PUBLIC_FUNC(EggPistonsMKII_State_ClassicMode); \
  IMPORT_PUBLIC_FUNC(EggPistonsMKII_State_PinchMode); \
  IMPORT_PUBLIC_FUNC(EggPistonsMKII_State_Destroyed); \
  IMPORT_PUBLIC_FUNC(EggPistonsMKII_Hit); \
  REGISTER_ENEMY(EggPistonsMKII)