#include "Debris.h"

ObjectDebris *Debris;
void (*Debris_State_Move)(void);
void (*Debris_State_FallAndFlicker)(void);