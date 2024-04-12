#pragma once

extern ObjectHUD* HUD;

// =============================================================================

// Functions -------------------------------------------------------------------

// =============================================================================
void HUD_LateUpdate_OVERLOAD();

#define OBJ_HUD_SETUP \
  MOD_REGISTER_OBJ_OVERLOAD(HUD, NULL, HUD_LateUpdate_OVERLOAD, NULL, NULL, NULL, NULL, NULL, NULL, NULL)
