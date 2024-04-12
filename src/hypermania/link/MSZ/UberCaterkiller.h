#pragma once

extern ObjectUberCaterkiller* UberCaterkiller;

extern void (*UberCaterkiller_State_HorizontalJump)();
extern void (*UberCaterkiller_State_FirstJump)();
extern void (*UberCaterkiller_State_RepeatedJumps)();
extern void (*UberCaterkiller_Hit)();

void UberCaterkiller_EnemyInfoHook();

#define OBJ_UBERCATERKILLER_SETUP \
  IMPORT_PUBLIC_FUNC(UberCaterkiller_State_HorizontalJump); \
  IMPORT_PUBLIC_FUNC(UberCaterkiller_State_FirstJump); \
  IMPORT_PUBLIC_FUNC(UberCaterkiller_State_RepeatedJumps); \
  IMPORT_PUBLIC_FUNC(UberCaterkiller_Hit); \
  REGISTER_ENEMY(UberCaterkiller)