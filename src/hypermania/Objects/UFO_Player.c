#include "UFO_Player.h"

ObjectUFO_Player *UFO_Player;

const char* names[5] = {
	"SONIC",
	"TAILS",
	"KNUCKLES",
	"MIGHTY",
	"RAY"
};

bool32 UFO_Player_State_UFOCaught_Released_HOOK(bool32 skippedState) {
	RSDK_THIS(UFO_Player);

	self->gravityStrength -= 0x80;

	self->position.x += self->velocity.x;
	self->position.y += self->velocity.y;
	self->height += self->gravityStrength;

	++self->timer;
	self->angleX = (self->angleX - (UFO_Player->maxSpeed >> 13)) & 0x3FF;

	if (self->timer == 16) {
		if (HPZ_SuperSpecialStage) {
			HM_global.currentSave->superEmeralds |= 1 << UFO_Setup->specialStageID;
			EntityUFO_Setup *setup = RSDK_GET_ENTITY(SLOT_UFO_SETUP, UFO_Setup);

			HM_global.currentSave->superEmeralds |= 1 << UFO_Setup->specialStageID;

			foreach_all(UFO_Player, player) {
				player->stateInput  = StateMachine_None;
				player->interaction = false;
			}

			setup->visible = true;
			setup->state   = UFO_Setup_State_FinishFadeout;

			RSDK.PlaySfx(UFO_Setup->sfxSSExit, false, 0xFF);
			Music_FadeOut(0.025);
			PauseMenu->disableEvents = true;

			// blegh
			int32 id = 0;
			switch(globals->playerID) {
				case ID_TAILS: id = 1; break;
				case ID_KNUCKLES: id = 2; break;
				case ID_MIGHTY: id = 3; break;
				case ID_RAY: id = 4; break;
			}

			printf("\n================================================================================\n");
			if (HM_global.currentSave->superEmeralds == 0b01111111) {
				printf("%s GOT ALL SUPER EMERALDS\n", names[id]);
				printf("NOW %s CAN BE HYPER %s\n", names[id], names[id]);
			} else {
				printf("%s GOT A SUPER EMERALD\n", names[id]);
			}
			printf("================================================================================\n\n");
		} else {
			UFO_Setup_Finish_Win();
		}
	}
	return true;
}