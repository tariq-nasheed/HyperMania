#include "SpecialRing.h"
#include "Zone.h"


// -----------------------------------------------------------------------------
ObjectSpecialRing *SpecialRing;
void (*SpecialRing_State_Flash)(void);

// -----------------------------------------------------------------------------
color ColorCycle[6] = { 0xF0F000, 0xfCD8FC,  0xB4D8FC, 0x90FC90,  0xD8fC6C,  0xFCD86C };


// -----------------------------------------------------------------------------
bool32 IsHPZStage() {
	// check if applicable to enter super emerald altar
	//printf("%i\n", SaveGame->saveRAM->chaosEmeralds);
	return true;
}

void SpecialRing_Draw_Hook(void) {
	RSDK_THIS(SpecialRing);

	if (self->state == SpecialRing_State_Flash) {
		self->direction = self->warpAnimator.frameID > 8;
		RSDK.DrawSprite(&self->warpAnimator, NULL, false);
	} else {
		RSDK.Prepare3DScene(SpecialRing->sceneIndex);
		if (self->enabled) {
			uint32 index = (Zone->timer / 4) % 6;
			if (IsHPZStage()) {
				RSDK.AddModelTo3DScene(SpecialRing->modelIndex, SpecialRing->sceneIndex, S3D_SOLIDCOLOR_SHADED_BLENDED, &self->matWorld, &self->matNormal, ColorCycle[index]);
			} else {
				RSDK.AddModelTo3DScene(SpecialRing->modelIndex, SpecialRing->sceneIndex, S3D_SOLIDCOLOR_SHADED_BLENDED, &self->matWorld, &self->matNormal, 0xF0F000);
			}
		} else {
			RSDK.AddModelTo3DScene(SpecialRing->modelIndex, SpecialRing->sceneIndex, S3D_WIREFRAME_SHADED, &self->matWorld, &self->matNormal, 0x609090);
		}
		RSDK.Draw3DScene(SpecialRing->sceneIndex);
	}
}

bool32 SpecialRing_State_Warp_Hook(bool32 skippedState) {
	RSDK_THIS(SpecialRing);
	if (self->warpTimer == 30 && IsHPZStage()) {
		//SaveGame_SaveGameState();
		//RSDK.PlaySfx(SpecialRing->sfxSpecialWarp, false, 0xFE);
		//destroyEntity(self);

		/*SaveRAM *saveRAM       = SaveGame->saveRAM;
		saveRAM->storedStageID = SceneInfo->listPos;

#if MANIA_USE_PLUS
		if (globals->gameMode == MODE_ENCORE) SceneInfo->listPos += 7;
#endif*/
		RSDK.SetScene("HyperMania", "Hidden Palace");
		return true;
	}
	return false;
}