#include "HUD.h"

ObjectHUD *HUD;


// -----------------------------------------------------------------------------
void HUD_LateUpdate_OVERLOAD() {
	Mod.Super(HUD->classID, SUPER_LATEUPDATE, NULL);
	RSDK_THIS(HUD);

#if GAME_VERSION != VER_100
	if (HM_global.currentSave->transferedEmeralds && HM_global.currentSave->superEmeralds != 0b01111111) {
		self->actionPromptPos = -TO_FIXED(32);
	}
#endif
}