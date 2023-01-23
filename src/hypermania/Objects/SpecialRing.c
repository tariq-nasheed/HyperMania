#include "SpecialRing.h"
#include "Zone.h"


// -----------------------------------------------------------------------------
ObjectSpecialRing *SpecialRing;
void (*SpecialRing_State_Flash)(void);
void (*SpecialRing_State_Warp)(void);

// -----------------------------------------------------------------------------
color ColorCycle[6] = { 0xF0F000, 0xfCD8FC,  0xB4D8FC, 0x90FC90,  0xD8fC6C,  0xFCD86C };


// -----------------------------------------------------------------------------
bool32 IsHPZStage() {
	return SaveGame_GetSaveRAM()->chaosEmeralds == 0b01111111;
}

bool32 SpecialRing_State_Idle_HOOK(bool32 skippedState) {
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
					if ((saveRAM->chaosEmeralds != 0b01111111 || HM_global.currentSave->superEmeralds != 0b01111111) && self->id) {
#else
					if (saveRAM->chaosEmeralds != 0b01111111 || HM_global.currentSave->superEmeralds != 0b01111111) {
#endif
						player->visible        = false;
						player->active         = ACTIVE_NEVER;
						SceneInfo->timeEnabled = false;
					}
					else {
						Player_GiveRings(player, 50, true);
					}
					if (self->id > 0) {
						if (saveRAM->chaosEmeralds != 0b01111111 || HM_global.currentSave->superEmeralds != 0b01111111)
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

bool32 SpecialRing_State_Flash_HOOK(bool32 skippedState) {
	RSDK_THIS(SpecialRing);
	RSDK.ProcessAnimation(&self->warpAnimator);

	if (!(Zone->timer & 3)) {
		for (int32 i = 0; i < 3; ++i) {
			int32 x             = self->position.x + RSDK.Rand(-TO_FIXED(32), TO_FIXED(2)) + self->sparkleRadius;
			int32 y             = self->position.y + RSDK.Rand(-TO_FIXED(32), TO_FIXED(32));
			EntityRing *sparkle = CREATE_ENTITY(Ring, NULL, x, y);

			sparkle->state     = Ring_State_Sparkle;
			sparkle->stateDraw = Ring_Draw_Sparkle;
			sparkle->active    = ACTIVE_NORMAL;
			sparkle->visible   = false;
			sparkle->drawGroup = Zone->objectDrawGroup[0];
			RSDK.SetSpriteAnimation(Ring->aniFrames, i % 3 + 2, &sparkle->animator, true, 0);
			int32 cnt = sparkle->animator.frameCount;
			if (sparkle->animator.animationID == 2) {
			    sparkle->alpha = 0xE0;
			    cnt >>= 1;
			}
			sparkle->maxFrameCount  = cnt - 1;
			sparkle->animator.speed = RSDK.Rand(6, 8);
			sparkle->timer          = 2 * i;
		}

		self->sparkleRadius -= TO_FIXED(8);
	}

#if GAME_VERSION != VER_100
	SaveRAM *saveRAM = SaveGame_GetSaveRAM();
	if ((saveRAM->chaosEmeralds == 0b01111111 && HM_global.currentSave->superEmeralds == 0b01111111) || !self->id) {
#else
	if (saveRAM->chaosEmeralds == 0b01111111 && HM_global.currentSave->superEmeralds == 0b01111111) {
#endif
		destroyEntity(self);
	} else if (self->warpAnimator.frameID == self->warpAnimator.frameCount - 1) {
		self->warpTimer = 0;
		self->visible   = false;
		self->state     = (saveRAM->chaosEmeralds != 0b01111111) ? SpecialRing_State_Warp
		                                                         : SpecialRing_State_HPZ_Warp;
	}

	return true;
}

void SpecialRing_Draw_OVERLOAD() {
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

void SpecialRing_State_HPZ_Warp() {
	RSDK_THIS(SpecialRing);

	if (++self->warpTimer == 30) {
		SaveGame_SaveGameState();
		RSDK.PlaySfx(SpecialRing->sfxSpecialWarp, false, 0xFE);
		destroyEntity(self);

		SaveRAM *saveRAM       = SaveGame_GetSaveRAM();
		saveRAM->storedStageID = SceneInfo->listPos;
		RSDK.SetScene("HyperMania", "Hidden Palace");
		//SceneInfo->listPos += saveRAM->nextSpecialStage;
#if MANIA_USE_PLUS
		//if (globals->gameMode == MODE_ENCORE) SceneInfo->listPos += 7;
#endif
		Zone_StartFadeOut(10, 0xF0F0F0);
		Music_FadeOut(1.0);
	}
}