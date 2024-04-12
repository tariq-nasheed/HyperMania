#pragma once

#if MANIA_USE_PLUS
  extern ObjectGigaMetal* GigaMetal;

  extern void (*GigaMetal_StateBody_Marching)();
  extern void (*GigaMetal_Hit)();

  void GigaMetal_EnemyInfoHook();

  #define OBJ_GIGAMETAL_SETUP \
    IMPORT_PUBLIC_FUNC(GigaMetal_StateBody_Marching); \
    IMPORT_PUBLIC_FUNC(GigaMetal_Hit); \
    REGISTER_ENEMY(GigaMetal)

#else
  #define OBJ_GIGAMETAL_SETUP
#endif