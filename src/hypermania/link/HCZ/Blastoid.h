#pragma once

extern ObjectBlastoid* Blastoid;

extern void (*Blastoid_State_Projectile)();

void Blastoid_EnemyInfoHook();

#define OBJ_BLASTOID_SETUP \
  IMPORT_PUBLIC_FUNC(Blastoid_State_Projectile); \
  REGISTER_ENEMY(Blastoid)