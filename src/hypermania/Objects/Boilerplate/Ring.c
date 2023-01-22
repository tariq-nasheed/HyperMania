#include "Ring.h"

ObjectRing *Ring;
void (*Ring_State_Lost)(void);
void (*Ring_Draw_Normal)(void);
void (*Ring_State_Sparkle)(void);
void (*Ring_Draw_Sparkle)(void);