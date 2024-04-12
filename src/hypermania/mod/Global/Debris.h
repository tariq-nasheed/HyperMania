#pragma once

extern ObjectDebris* Debris;

extern void (*Debris_State_Move)();
extern void (*Debris_State_FallAndFlicker)();

void Debris_Draw_OVERLOAD();

#define OBJ_DEBRIS_SETUP \
  MOD_REGISTER_OBJ_OVERLOAD(Debris, NULL, NULL, NULL, Debris_Draw_OVERLOAD, NULL, NULL, NULL, NULL, NULL)