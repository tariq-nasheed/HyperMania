#pragma once

extern ObjectHotaruMKII* HotaruMKII;

extern void (*HotaruMKII_State_Charging)();
extern void (*HotaruMKII_State_LaserAttack)();

void HotaruMKII_EnemyInfoHook();

#define OBJ_HOTARUMKII_SETUP \
  IMPORT_PUBLIC_FUNC(HotaruMKII_State_Charging); \
  IMPORT_PUBLIC_FUNC(HotaruMKII_State_LaserAttack); \
  REGISTER_ENEMY(HotaruMKII)