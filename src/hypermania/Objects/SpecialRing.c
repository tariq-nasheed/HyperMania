#include "SpecialRing.h"
#include "Zone.h"


// -----------------------------------------------------------------------------
ObjectSpecialRing *SpecialRing;
void (*SpecialRing_State_Flash)(void);

// -----------------------------------------------------------------------------
color ColorCycle[6] = { 0xF0F000, 0xfCD8FC,  0xB4D8FC, 0x90FC90,  0xD8fC6C,  0xFCD86C };


// -----------------------------------------------------------------------------
bool32 IsHPZStage() {
	return SaveGame_GetSaveRAM()->chaosEmeralds == 0b01111111;
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

bool32 SpecialRing_State_Idle(bool32 skippedState) {
	RSDK_THIS(SpecialRing);

	self->angleZ = (self->angleZ + 4) & 0x3FF;
	self->angleY = (self->angleY + 4) & 0x3FF;

	Vector2 range;
	range.x = TO_FIXED(128);
	range.y = TO_FIXED(128);
	if (!RSDK.CheckOnScreen(self, &range))
		self->scale.x = 0;

	if (self->scale.x >= 0x140)
		self->scale.x = 0x140;
	else
		self->scale.x += ((0x168 - self->scale.x) >> 5);

	RSDK.MatrixScaleXYZ(&self->matTransform, self->scale.x, self->scale.x, self->scale.x);
	RSDK.MatrixTranslateXYZ(&self->matTransform, self->position.x, self->position.y, 0, false);
	RSDK.MatrixRotateXYZ(&self->matWorld, 0, self->angleY, self->angleZ);
	RSDK.MatrixMultiply(&self->matWorld, &self->matWorld, &self->matTransform);
	RSDK.MatrixRotateX(&self->matTempRot, 0x1E0);
	RSDK.MatrixRotateXYZ(&self->matNormal, 0, self->angleY, self->angleZ);
	RSDK.MatrixMultiply(&self->matNormal, &self->matNormal, &self->matTempRot);

	if (self->enabled && self->scale.x > 0x100) {
		foreach_active(Player, player) {
			if ((self->planeFilter <= 0 || player->collisionPlane == (((uint8)self->planeFilter - 1) & 1)) && !player->sidekick) {
				if (Player_CheckCollisionTouch(player, self, &SpecialRing->hitbox) && SceneInfo->timeEnabled) {
					self->sparkleRadius = TO_FIXED(16);
					self->state         = SpecialRing_State_Flash;

					SaveRAM *saveRAM = SaveGame_GetSaveRAM();
#if GAME_VERSION != VER_100
					if ((saveRAM->chaosEmeralds != 0b01111111 || localHM_SaveRam.superEmeralds != 0b01111111) && self->id) {
#else
					if (saveRAM->chaosEmeralds != 0b01111111 || localHM_SaveRam.superEmeralds != 0b01111111) {
#endif
						player->visible        = false;
						player->active         = ACTIVE_NEVER;
						SceneInfo->timeEnabled = false;
					}
					else {
						Player_GiveRings(player, 50, true);
					}

					if (self->id > 0) {
						if (saveRAM->chaosEmeralds != 0b01111111 || localHM_SaveRam.superEmeralds != 0b01111111)
							globals->specialRingID = self->id;
						saveRAM->collectedSpecialRings |= 1 << (16 * Zone->actID - 1 + self->id);
					}

					RSDK.PlaySfx(SpecialRing->sfxSpecialRing, false, 0xFE);
				}
			}
		}
	}
	return true;
}

bool32 SpecialRing_State_Warp_Hook(bool32 skippedState) {
	RSDK_THIS(SpecialRing);
	if (self->warpTimer == 30 && IsHPZStage()) {
		//SaveGame_SaveGameState();
		//RSDK.PlaySfx(SpecialRing->sfxSpecialWarp, false, 0xFE);
		//destroyEntity(self);

		/*SaveRAM *saveRAM	   = SaveGame->saveRAM;
		saveRAM->storedStageID = SceneInfo->listPos;

#if MANIA_USE_PLUS
		if (globals->gameMode == MODE_ENCORE) SceneInfo->listPos += 7;
#endif*/
		RSDK.SetScene("HyperMania", "Hidden Palace");
		return true;
	}
	return false;
}