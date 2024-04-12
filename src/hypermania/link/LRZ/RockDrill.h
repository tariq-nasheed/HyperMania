#pragma once

extern ObjectRockDrill* RockDrill;

extern void (*RockDrill_State_Drilling)();

void RockDrill_EnemyInfoHook();

#define OBJ_ROCKDRILL_SETUP \
  IMPORT_PUBLIC_FUNC(RockDrill_State_Drilling); \
  REGISTER_ENEMY(RockDrill)