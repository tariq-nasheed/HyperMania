#pragma once

extern ObjectBubbler* Bubbler;

extern void (*Bubbler_StateProjectile_Seed)();
extern void (*Bubbler_StateProjectile_Bubbler)();

void Bubbler_EnemyInfoHook();

#define OBJ_BUBBLER_SETUP \
  IMPORT_PUBLIC_FUNC(Bubbler_StateProjectile_Seed); \
  IMPORT_PUBLIC_FUNC(Bubbler_StateProjectile_Bubbler); \
  REGISTER_ENEMY(Bubbler)