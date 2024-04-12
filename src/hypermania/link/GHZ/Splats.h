#pragma once

extern ObjectSplats* Splats;

extern void (*Splats_State_BounceAround)();
extern void (*Splats_State_JumpOutOfJar)();
extern void (*Splats_State_HandleBouncing)();
extern void (*Splats_State_HandleLanding)();
extern void (*Splats_State_NoMoreJumps)();

void Splats_EnemyInfoHook();

#define OBJ_SPLATS_SETUP \
  IMPORT_PUBLIC_FUNC(Splats_State_BounceAround); \
  IMPORT_PUBLIC_FUNC(Splats_State_JumpOutOfJar); \
  IMPORT_PUBLIC_FUNC(Splats_State_HandleBouncing); \
  IMPORT_PUBLIC_FUNC(Splats_State_HandleLanding); \
  IMPORT_PUBLIC_FUNC(Splats_State_NoMoreJumps); \
  REGISTER_ENEMY(Splats)