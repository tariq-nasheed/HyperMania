#pragma once

extern ObjectHeavyMystic* HeavyMystic;

extern void (*HeavyMystic_Hit)();
extern void (*HeavyMystic_StateBoss_RougeHit)();
extern void (*HeavyMystic_StateBoss_MysticReveal)();
extern void (*HeavyMystic_StateBoss_FangIdle)();
extern void (*HeavyMystic_StateBoss_FangTell)();
extern void (*HeavyMystic_StateBoss_FangHop)();
extern void (*HeavyMystic_StateBoss_BarkIdle)();
extern void (*HeavyMystic_StateBoss_BarkPounding)();
extern void (*HeavyMystic_StateBoss_BarkJump)();
extern void (*HeavyMystic_StateBoss_BeanIdle)();
extern void (*HeavyMystic_StateBoss_BeanBomb1Throw)();
extern void (*HeavyMystic_StateBoss_BeanBomb2Throw)();
extern void (*HeavyMystic_StateBoss_BeanJump)();

void HeavyMystic_EnemyInfoHook();

#define OBJ_HEAVYMYSTIC_SETUP \
  IMPORT_PUBLIC_FUNC(HeavyMystic_Hit); \
  HeavyMystic_StateBoss_RougeHit = Mod.GetPublicFunction(NULL, "HeavyMystic_StateBoss_RougeHit"); \
  if (!HeavyMystic_StateBoss_RougeHit) HeavyMystic_StateBoss_RougeHit = Mod.GetPublicFunction(NULL, "HeavyMystic_StateBoss_RogueHit"); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_MysticReveal); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_FangIdle); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_FangTell); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_FangHop); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BarkIdle); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BarkPounding); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BarkJump); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BeanIdle); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BeanBomb1Throw); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BeanBomb2Throw); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BeanJump); \
  REGISTER_ENEMY(HeavyMystic)