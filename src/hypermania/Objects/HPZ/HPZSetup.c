#include "HPZSetup.h"
#include "HPZIntro.h"

ObjectHPZSetup* HPZSetup;

void HPZSetup_Update(void) {}
void HPZSetup_LateUpdate(void) {}

void HPZSetup_StaticUpdate(void) {
	SceneInfo->timeEnabled = false;
}

void HPZSetup_Draw(void) {}
void HPZSetup_Create(void *data) {}

void HPZSetup_StageLoad(void) {
	Zone_StartFadeIn(30, 0xF0F0F0);
	Zone->cameraBoundsL[0] = 2560;
	Zone->cameraBoundsR[0] = 3200;

	if (!HPZ_results) {
		Entity* player = RSDK_GET_ENTITY_GEN(0);
		CREATE_ENTITY(HPZIntro, NULL, player->position.x, player->position.y);
	}

#if MANIA_USE_PLUS
	if (globals->gameMode == MODE_ENCORE) {
		RSDK.LoadPalette(0, "EncoreLRZ3.act", 0b0000000011111111);
		RSDK.CopyPalette(0, 240, 1, 240, 16);
	}
#endif
}

void HPZSetup_EditorDraw(void) {}
void HPZSetup_EditorLoad(void) {}

void HPZSetup_Serialize(void) {}
