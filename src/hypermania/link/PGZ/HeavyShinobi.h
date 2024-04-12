#pragma once

extern ObjectHeavyShinobi* HeavyShinobi;

void HeavyShinobi_EnemyInfoHook(void);
extern void (*HeavyShinobi_State_Idle)();
extern void (*HeavyShinobi_State_Slash)();
extern void (*HeavyShinobi_State_Jump)();
extern void (*HeavyShinobi_State_Glitched)();
extern void (*HeavyShinobi_State_Destroyed)();

#define OBJ_HEAVYSHINOBI_SETUP \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Idle); \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Slash); \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Jump); \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Glitched); \
  IMPORT_PUBLIC_FUNC(HeavyShinobi_State_Destroyed); \
  REGISTER_ENEMY(HeavyShinobi)