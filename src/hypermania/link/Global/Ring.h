#pragma once

extern ObjectRing *Ring;

// Imported Functions
extern void (*Ring_State_Lost)(void);
extern void (*Ring_Draw_Normal)(void);
extern void (*Ring_State_Sparkle)(void);
extern void (*Ring_Draw_Sparkle)(void);
extern void (*Ring_Collect)(void);

#define OBJ_RING_SETUP \
  IMPORT_PUBLIC_FUNC(Ring_State_Lost); \
  IMPORT_PUBLIC_FUNC(Ring_State_Lost); \
  IMPORT_PUBLIC_FUNC(Ring_State_Sparkle); \
  IMPORT_PUBLIC_FUNC(Ring_Draw_Sparkle); \
  IMPORT_PUBLIC_FUNC(Ring_Collect); \
  MOD_REGISTER_OBJECT_HOOK(Ring)