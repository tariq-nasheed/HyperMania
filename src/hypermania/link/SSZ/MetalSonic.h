#pragma once

extern ObjectMetalSonic* MetalSonic;

// hopefully this works because i dont feel like compiling a pre-mania Game.so to test it lol
#if !MANIA_USE_PLUS
  extern void (*MetalSonic_State_Hover_Phase2)();
  extern void (*MetalSonic_State_FinishAttack_Phase2)();
  extern void (*MetalSonic_Hit)();

  void MetalSonic_EnemyInfoHook();

  #define OBJ_METALSONIC_SETUP \
    IMPORT_PUBLIC_FUNC(MetalSonic_State_Hover_Phase2); \
    IMPORT_PUBLIC_FUNC(MetalSonic_State_FinishAttack_Phase2); \
    IMPORT_PUBLIC_FUNC(MetalSonic_Hit); \
    REGISTER_ENEMY(MetalSonic)
#else
  #define OBJ_METALSONIC_SETUP
#endif