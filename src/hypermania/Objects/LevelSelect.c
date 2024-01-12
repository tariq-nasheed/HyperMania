#include "LevelSelect.h"

ObjectLevelSelect* LevelSelect;

void LevelSelect_StageLoad_OVERLOAD() {
	Mod.Super(LevelSelect->classID, SUPER_STAGELOAD, NULL);
#if MANIA_USE_PLUS
	LevelSelect->checkCheatActivated[1] = LevelSelect_Cheat_AllEmeralds;
#endif
}

void LevelSelect_Cheat_AllEmeralds() {
	Music_FadeOut(0.125);
	RSDK.PlaySfx(LevelSelect->sfxEmerald, false, 255);

	SaveRAM* saveRAM = GetSaveRAM_Safe();
	if (saveRAM->chaosEmeralds != 0b01111111) {
		saveRAM->chaosEmeralds = 0b01111111;
	} else {
		HM_globals->currentSave->transferedEmeralds = 0b01111111;
		HM_globals->currentSave->superEmeralds = 0b01111111;
	}
}