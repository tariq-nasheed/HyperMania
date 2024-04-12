#pragma once

extern ObjectBlaster* Blaster;

extern void (*Blaster_State_BeginShot)();
extern void (*Blaster_State_Shot)();
extern void (*Blaster_State_Shell)();

void Blaster_EnemyInfoHook();

#define OBJ_BLASTER_SETUP \
  IMPORT_PUBLIC_FUNC(Blaster_State_BeginShot); \
  IMPORT_PUBLIC_FUNC(Blaster_State_Shot); \
  IMPORT_PUBLIC_FUNC(Blaster_State_Shell); \
  REGISTER_ENEMY(Blaster)