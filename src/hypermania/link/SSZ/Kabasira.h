#pragma once

extern ObjectKabasira* Kabasira;

extern void (*Kabasira_State_Moving)();

void Kabasira_EnemyInfoHook();

#define OBJ_KABASIRA_SETUP \
  IMPORT_PUBLIC_FUNC(Kabasira_State_Moving); \
  REGISTER_ENEMY(Kabasira)