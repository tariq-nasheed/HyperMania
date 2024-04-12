#pragma once

extern ObjectCaterkillerJr* CaterkillerJr;

void CaterkillerJr_EnemyInfoHook();

#define OBJ_CATERKILLERJR_SETUP \
  REGISTER_ENEMY(CaterkillerJr)