#pragma once

// =============================================================================

// Definitions -----------------------------------------------------------------

// =============================================================================
extern ObjectSpecialRing* SpecialRing;

// =============================================================================

// Functions -------------------------------------------------------------------

// =============================================================================
extern void (*SpecialRing_State_Flash)();
extern void (*SpecialRing_State_Warp)();

void SpecialRing_State_HPZ_Warp();

bool32 SpecialRing_State_Idle_HOOK(bool32);
bool32 SpecialRing_State_Flash_HOOK(bool32);

void SpecialRing_StageLoad_OVERLOAD();
void SpecialRing_Draw_OVERLOAD();

#define OBJ_SPECIALRING_SETUP \
  IMPORT_PUBLIC_FUNC(SpecialRing_State_Flash); \
  IMPORT_PUBLIC_FUNC(SpecialRing_State_Warp); \
  HOOK_STATE(SpecialRing_State_Idle, 1); \
  HOOK_IMPORTED_STATE(SpecialRing_State_Flash, 1); \
  MOD_REGISTER_OBJ_OVERLOAD(SpecialRing, NULL, NULL, NULL, SpecialRing_Draw_OVERLOAD, NULL, SpecialRing_StageLoad_OVERLOAD, NULL, NULL, NULL)
