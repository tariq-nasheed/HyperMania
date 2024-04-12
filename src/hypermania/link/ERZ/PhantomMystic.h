#pragma once

extern ObjectPhantomMystic* PhantomMystic;

extern void (*PhantomMystic_State_CupBlast)();
extern void (*PhantomMystic_State_MoveCupsToMystic)();
extern void (*PhantomMystic_Hit)();

void PhantomMystic_EnemyInfoHook();

#define OBJ_PHANTOMMYSTIC_SETUP \
  IMPORT_PUBLIC_FUNC(PhantomMystic_State_CupBlast); \
  IMPORT_PUBLIC_FUNC(PhantomMystic_State_MoveCupsToMystic); \
  IMPORT_PUBLIC_FUNC(PhantomMystic_Hit); \
  REGISTER_ENEMY(PhantomMystic)