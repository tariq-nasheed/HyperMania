#pragma once

extern ObjectJuggleSaw* JuggleSaw;

extern void (*JuggleSaw_StateCrab_Handle)();
extern void (*JuggleSaw_StateCrab_ThrowSaw)();

void JuggleSaw_EnemyInfoHook();

#define OBJ_JUGGLESAW_SETUP \
  IMPORT_PUBLIC_FUNC(JuggleSaw_StateCrab_Handle); \
  IMPORT_PUBLIC_FUNC(JuggleSaw_StateCrab_ThrowSaw); \
  REGISTER_ENEMY(JuggleSaw)