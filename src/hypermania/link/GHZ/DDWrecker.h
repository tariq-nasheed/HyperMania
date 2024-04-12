#pragma once

extern ObjectDDWrecker* DDWrecker;

extern void (*DDWrecker_StateBall_Vulnerable)();
extern void (*DDWrecker_StateBall_Spiked)();
extern void (*DDWrecker_StateBall_Partnerless)();
extern void (*DDWrecker_Hit)();

void DDWrecker_EnemyInfoHook();

#define OBJ_DDWRECKER_SETUP \
  IMPORT_PUBLIC_FUNC(DDWrecker_StateBall_Vulnerable); \
  IMPORT_PUBLIC_FUNC(DDWrecker_StateBall_Spiked); \
  IMPORT_PUBLIC_FUNC(DDWrecker_StateBall_Partnerless); \
  IMPORT_PUBLIC_FUNC(DDWrecker_Hit); \
  REGISTER_ENEMY(DDWrecker)