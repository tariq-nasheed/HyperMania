#pragma once

extern ObjectUFO_Player *UFO_Player;

bool32 UFO_Player_State_UFOCaught_Released_HOOK(bool32);

#define OBJ_UFO_PLAYER_SETUP \
  HOOK_STATE(UFO_Player_State_UFOCaught_Released, 1); \
  MOD_REGISTER_OBJECT_HOOK(UFO_Player)
