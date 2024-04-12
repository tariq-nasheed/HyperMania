#pragma once

extern ObjectFireworm* Fireworm;

extern void (*Fireworm_State_FlyAround)();

void Fireworm_EnemyInfoHook();

#define OBJ_FIREWORM_SETUP \
  IMPORT_PUBLIC_FUNC(Fireworm_State_FlyAround); \
  REGISTER_ENEMY(Fireworm)