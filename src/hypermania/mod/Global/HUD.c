#include "HUD.h"

ObjectHUD *HUD;


// -----------------------------------------------------------------------------
void HUD_LateUpdate_OVERLOAD() {
	Mod.Super(HUD->classID, SUPER_LATEUPDATE, NULL);
	RSDK_THIS(HUD);

#if GAME_VERSION != VER_100
	if ((HM_globals->currentSave->transferedEmeralds || (HM_globals->config.superTailsOnly && GET_CHARACTER_ID(1) == ID_TAILS))
	&& HM_globals->currentSave->superEmeralds != 0b01111111) {
		self->actionPromptPos = -TO_FIXED(32);
	}
#endif
}