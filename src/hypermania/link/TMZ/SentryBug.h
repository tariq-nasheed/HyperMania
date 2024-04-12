#pragma once

extern ObjectSentryBug* SentryBug;

extern void (*SentryBug_State_AwaitPlayer)();
extern void (*SentryBug_State_DropOrbs)();
extern void (*SentryBug_State_NetAppear)();
extern void (*SentryBug_State_NetShrink)();
extern void (*SentryBug_State_NetFlash)();
extern void (*SentryBug_State_ReturnToSlots)();

void SentryBug_EnemyInfoHook();

#define OBJ_SENTRYBUG_SETUP \
  IMPORT_PUBLIC_FUNC(SentryBug_State_AwaitPlayer); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_DropOrbs); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_NetAppear); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_NetShrink); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_NetFlash); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_ReturnToSlots); \
  REGISTER_ENEMY(SentryBug)