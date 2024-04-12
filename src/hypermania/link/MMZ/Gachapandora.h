#pragma once

extern ObjectGachapandora* Gachapandora;

extern void (*Gachapandora_StatePrize_DrillerMove)();
extern void (*Gachapandora_StatePrize_FireDropperMove)();
extern void (*Gachapandora_StatePrize_AmyWalk)();
extern void (*Gachapandora_StatePrize_AmyIdle)();
extern void (*Gachapandora_StatePrize_Destroyed)();

void Gachapandora_EnemyInfoHook();

#define OBJ_GACHAPANDORA_SETUP \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_DrillerMove); \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_FireDropperMove); \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_AmyWalk); \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_AmyIdle); \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_Destroyed); \
  REGISTER_ENEMY(Gachapandora)