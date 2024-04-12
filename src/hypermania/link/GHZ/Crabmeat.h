#ifndef OBJ_CRABMEAT_LINK_H
#define OBJ_CRABMEAT_LINK_H

extern ObjectCrabmeat* Crabmeat;

extern void (*Crabmeat_State_Projectile)();

void Crabmeat_EnemyInfoHook();

#define OBJ_CRABMEAT_SETUP \
  IMPORT_PUBLIC_FUNC(Crabmeat_State_Projectile); \
  REGISTER_ENEMY(Crabmeat)

#endif
