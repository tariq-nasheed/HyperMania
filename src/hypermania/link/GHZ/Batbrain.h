#ifndef OBJ_BATBRAIN_LINK_H
#define OBJ_BATBRAIN_LINK_H

extern ObjectBatbrain* Batbrain;

void Batbrain_EnemyInfoHook();

#define OBJ_BATBRAIN_SETUP \
  REGISTER_ENEMY(Batbrain)

#endif