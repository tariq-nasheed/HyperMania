#pragma once

extern ObjectLevelSelect* LevelSelect;

// =============================================================================

// Functions -------------------------------------------------------------------

// =============================================================================
void LevelSelect_StageLoad_OVERLOAD();

#define OBJ_LEVELSELECT_SETUP \
  MOD_REGISTER_OBJ_OVERLOAD(LevelSelect, NULL, NULL, NULL, NULL, NULL, LevelSelect_StageLoad_OVERLOAD, NULL, NULL, NULL)

void LevelSelect_Cheat_AllEmeralds();
