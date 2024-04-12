#pragma once

extern ObjectPhantomShinobi* PhantomShinobi;

extern void (*PhantomShinobi_State_SetupAttack)();
extern void (*PhantomShinobi_State_Moving)();
extern void (*PhantomShinobi_State_PrepareFinAttack)();
extern void (*PhantomShinobi_State_ExtendFins)();
extern void (*PhantomShinobi_State_RetractFins)();
extern void (*PhantomShinobi_Hit)();

void PhantomShinobi_EnemyInfoHook();

#define OBJ_PHANTOMSHINOBI_SETUP \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_SetupAttack); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_Moving); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_PrepareFinAttack); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_ExtendFins); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_RetractFins); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_Hit); \
  REGISTER_ENEMY(PhantomShinobi)