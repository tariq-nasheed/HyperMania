#pragma once

extern ObjectJawz* Jawz;

extern void (*Jawz_State_Triggered)();

void Jawz_EnemyInfoHook();

#define OBJ_JAWZ_SETUP \
  IMPORT_PUBLIC_FUNC(Jawz_State_Triggered); \
  REGISTER_ENEMY(Jawz)