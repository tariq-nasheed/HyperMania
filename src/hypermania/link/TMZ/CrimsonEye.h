#pragma once

extern ObjectCrimsonEye* CrimsonEye;

extern void (*CrimsonEye_StateCore_ContainerActive)();
extern void (*CrimsonEye_StateCore_Hovering)();
extern void (*CrimsonEye_StateCore_ImpactLift)();
extern void (*CrimsonEye_Hit)();

void CrimsonEye_EnemyInfoHook();

#define OBJ_CRIMSONEYE_SETUP \
  IMPORT_PUBLIC_FUNC(CrimsonEye_StateCore_ContainerActive); \
  IMPORT_PUBLIC_FUNC(CrimsonEye_StateCore_Hovering); \
  IMPORT_PUBLIC_FUNC(CrimsonEye_StateCore_ImpactLift); \
  IMPORT_PUBLIC_FUNC(CrimsonEye_Hit); \
  REGISTER_ENEMY(CrimsonEye)