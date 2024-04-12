#pragma once

extern ObjectPhantomShield* PhantomShield;
extern ObjectPhantomEgg* PhantomEgg;

extern void (*PhantomEgg_State_MoveAround)();
extern void (*PhantomEgg_State_Attack_Jumped)();
extern void (*PhantomEgg_State_Attack_JumpLand)();
extern void (*PhantomEgg_State_Attack_JumpAttack)();
extern void (*PhantomEgg_State_Attack_CableShock)();
extern void (*PhantomEgg_Hit)();

void PhantomEgg_EnemyInfoHook();

#define OBJ_PHANTOMEGG_SETUP \
  MOD_REGISTER_OBJECT_HOOK(PhantomShield); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_MoveAround); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_Attack_Jumped); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_Attack_JumpLand); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_Attack_JumpAttack); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_Attack_CableShock); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_Hit); \
  REGISTER_ENEMY(PhantomEgg)