#pragma once

extern ObjectBigSqueeze* BigSqueeze;

extern void (*BigSqueeze_StateBoss_Idle)();
extern void (*BigSqueeze_StateBoss_Electrified)();
extern void (*BigSqueeze_Hit)();

void BigSqueeze_EnemyInfoHook();

#define OBJ_BIGSQUEEZE_SETUP \
  IMPORT_PUBLIC_FUNC(BigSqueeze_StateBoss_Idle); \
  IMPORT_PUBLIC_FUNC(BigSqueeze_StateBoss_Electrified); \
  IMPORT_PUBLIC_FUNC(BigSqueeze_Hit); \
  REGISTER_ENEMY(BigSqueeze)