#include "UFO_Setup.h"
#include "SpecialClear.h"
#include "HPZ/HPZIntro.h"


ObjectUFO_Setup *UFO_Setup;
void (*UFO_Setup_State_FinishFadeout)();
void (*UFO_Setup_Finish_Win)();

UFO_HPZbuffer_t UFO_HPZbuffer;
static bool32 HPZ_results;

bool32 UFO_Setup_State_FinishFadeout_HOOK(bool32 skippedState) {
	RSDK_THIS(UFO_Setup);
	// TODO check if player has all chaos emeralds or last special stage was for a super emerald
	if (self->timer >= 1024 && !UFO_Setup->resetToTitle && HPZ_SuperSpecialStage) {
		HPZ_results = true;
		RSDK.SetScene("HyperMania", "Hidden Palace");
		RSDK.LoadScene();
		UFO_HPZbuffer.timedOut = UFO_Setup->timedOut;
		UFO_HPZbuffer.machLevel = UFO_Setup->machLevel;
		UFO_HPZbuffer.scoreBonus = UFO_Setup->scoreBonus;
		UFO_HPZbuffer.rings = UFO_Setup->rings;
		UFO_HPZbuffer.specialStageID = UFO_Setup->specialStageID;
		self->visible = false;
		self->state   = StateMachine_None;
	}
	return false;

}


void SetupHPZResults(void* data) {
	UNUSED(data);

	if (Zone) {
		if (HPZ_results) {
			if (Zone->timer == 2) {
				HPZ_results = false;
				foreach_active(Player, player) {
					player->visible = false;
					player->active  = ACTIVE_NEVER;
				}
				RSDK.ResetEntitySlot(1, SpecialClear->classID, NULL);
			} else {
				Music_FadeOut(1.0);
			}
		}
	}
}