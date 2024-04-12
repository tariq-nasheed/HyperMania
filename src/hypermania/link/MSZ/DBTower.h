#pragma once

extern ObjectDBTower* DBTower;

extern void (*DBTower_State_HandleBoss)();
extern void (*DBTower_State_Destroyed)();

void DBTower_EnemyInfoHook();

#define OBJ_DBTOWER_SETUP \
  IMPORT_PUBLIC_FUNC(DBTower_State_HandleBoss); \
  IMPORT_PUBLIC_FUNC(DBTower_State_Destroyed); \
  REGISTER_ENEMY(DBTower)