#pragma once

extern ObjectFBZTrash* FBZTrash;

extern void (*FBZTrash_State_OrbinautMove)();

void FBZTrash_EnemyInfoHook();

#define OBJ_FBZTRASH_SETUP \
  IMPORT_PUBLIC_FUNC(FBZTrash_State_OrbinautMove); \
  REGISTER_ENEMY(FBZTrash)