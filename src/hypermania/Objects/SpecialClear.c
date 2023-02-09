#include "SpecialClear.h"


// -----------------------------------------------------------------------------
ObjectSpecialClear *SpecialClear;
SpecialClearStaticExt_t SpecialClearStaticExt;

void (*SpecialClear_State_EnterText)();
void (*SpecialClear_State_ExitFinishMessage)();
void (*SpecialClear_State_ExitResults)();
void (*SpecialClear_DrawNumbers)(Vector2 *pos, int32 value);

// -----------------------------------------------------------------------------
void SpecialClear_StageLoad_OVERLOAD() {
	Mod.Super(SpecialClear->classID, SUPER_STAGELOAD, NULL);
	SpecialClearStaticExt.SEAniFrames = RSDK.LoadSpriteAnimation("Special/ResultsSE.bin", SCOPE_STAGE);
	RSDK.SetSpriteAnimation(SpecialClearStaticExt.SEAniFrames, 0, &SpecialClearStaticExt.SEAnimator, true, 0);
}

void SpecialClear_Create_OVERLOAD(void* data) {
	// original SpecialClear_Create reads from UFO_Setup without NULL checking it so i have to do this :(
	RSDK_THIS(SpecialClear);

	if (!SceneInfo->inEditor) {
		self->active    = ACTIVE_NORMAL;
		self->visible   = true;
		self->drawGroup = 14;
		self->timer     = 512;
		self->fillColor = 0xF0F0F0;
		self->showFade  = true;
		self->state     = SpecialClear_State_SetupDelay;

		if (RSDK.CheckSceneFolder("SpecialBS")) {
			self->isBSS     = true;
			self->ringBonus = 100 * BSS_Setup->rings;
			if (!BSS_Setup->ringCount)
				self->perfectBonus = 50000;

			self->messageType = SC_MSG_SPECIALCLEAR;
		} else {
			if (UFO_Setup) RSDK.CopyPalette(7, 0, 0, 0, 128);

			self->isBSS     = false;
			if (UFO_Setup) {
				self->ringBonus = 100 * UFO_Setup->rings;
				self->machBonus = 1000 * (UFO_Setup->machLevel + 10 * UFO_Setup->scoreBonus);
			} else {
				self->ringBonus = 100 * UFO_HPZbuffer.rings;
				self->machBonus = 1000 * (UFO_HPZbuffer.machLevel + 10 * UFO_HPZbuffer.scoreBonus);
			}

			if (globals->gameMode < MODE_TIMEATTACK && self->machBonus + self->ringBonus >= 10000)
				self->hasContinues = true;

			SaveRAM *saveRAM = SaveGame_GetSaveRAM();
			self->score      = saveRAM->score;
			self->score1UP   = saveRAM->score1UP;
			self->lives      = saveRAM->lives;
			if ((UFO_Setup && saveRAM->chaosEmeralds == 0b01111111) || (!UFO_Setup && HM_global.currentSave->superEmeralds == 0b01111111)) {
				self->messageType = SC_MSG_ALLEMERALDS;
			} else {
				if (UFO_Setup) {
					self->messageType = !UFO_Setup->timedOut ? SC_MSG_GOTEMERALD : SC_MSG_SPECIALCLEAR;
				} else {
					self->messageType = !UFO_HPZbuffer.timedOut ? SC_MSG_GOTEMERALD : SC_MSG_SPECIALCLEAR;
				}
			}
		}

		self->messagePos1.x = 0x1400000;
		self->messagePos1.y = 0x580000;

		self->messagePos2.x = -0x1400000;
		self->messagePos2.y = 0x700000;

		self->scoreBonusPos.x = 0x1E80000;
		self->scoreBonusPos.y = 0x8C0000;

		self->ringBonusPos.x = 0x3080000;
		self->ringBonusPos.y = 0xAC0000;

		self->machBonusPos.x = 0x4280000;
		self->machBonusPos.y = 0xBC0000;

		self->perfectBonusPos.x = 0x4280000;
		self->perfectBonusPos.y = 0xBC0000;
		self->continuePos.x     = 0x5480000;
		self->continuePos.y     = 0xCC0000;

		if (UFO_Setup) RSDK.CopyPalette(1, 0, 0, 128, 48);

		for (int32 i = 0; i < 7; ++i) {
			self->emeraldPositions[i] = 0x1100000 + (i * 0x200000);
			self->emeraldSpeeds[i]    = -0xA0000 + (i * -0xA000);
		}

		RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_BONUS, &self->bonusAnimator, true, 0);
		RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_NUMBERS, &self->numbersAnimator, true, 0);
		RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_EMERALDS, &self->emeraldsAnimator, true, 0);
		switch (GET_CHARACTER_ID(1)) {
			default:
			case ID_SONIC: RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_SONIC, &self->playerNameAnimator, true, 0);
#if MANIA_USE_PLUS
				RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_SONIC);
#else
				RSDK.SetSpriteAnimation(SpecialClear->continueFrames, 0, &self->continueAnimator, true, SC_ANI_TAILS);
#endif
				break;

			case ID_TAILS: RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_TAILS, &self->playerNameAnimator, true, 0);
#if MANIA_USE_PLUS
				RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_TAILS);
#else
				RSDK.SetSpriteAnimation(SpecialClear->continueFrames, 0, &self->continueAnimator, true, SC_ANI_TAILS);
#endif
				break;

			case ID_KNUCKLES: RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_KNUX, &self->playerNameAnimator, true, 0);
#if MANIA_USE_PLUS
				RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_KNUX);
#else
				RSDK.SetSpriteAnimation(SpecialClear->continueFrames, 0, &self->continueAnimator, true, SC_ANI_TAILS);
#endif
				break;

#if MANIA_USE_PLUS
			case ID_MIGHTY:
				RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_MIGHTY, &self->playerNameAnimator, true, 0);
				RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, 3);
				break;

			case ID_RAY:
				RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_RAY, &self->playerNameAnimator, true, 0);
				RSDK.SetSpriteAnimation(SpecialClear->aniFrames, SC_ANI_CONTINUE, &self->continueAnimator, true, SC_ANI_RAY);
				break;
#endif
		}
	}
}

void SpecialClear_Update_OVERLOAD() {
	Mod.Super(SpecialClear->classID, SUPER_UPDATE, NULL);
	RSDK_THIS(SpecialClear);

	if (self->state == SpecialClear_State_ExitFinishMessage && !UFO_Setup && HM_global.currentSave->superEmeralds != 0b01111111) {
		self->timer    = 0;
		self->showFade = true;
		RSDK.PlaySfx(SpecialClear->sfxSpecialWarp, false, 0xFF);
		self->state = SpecialClear_State_ExitResults;
	}
}

void SpecialClear_Draw_OVERLOAD() {
	RSDK_THIS(SpecialClear);

	Vector2 vertPos[4];
	Vector2 drawPos;

	int32 centerX = ScreenInfo->center.x << 16;
	drawPos.x     = centerX - 0x600000;

	// Draw Emeralds
	if (UFO_Setup) {
		SaveRAM *saveRAM = SaveGame_GetSaveRAM();
		for (int32 i = 0; i < 7; ++i) {
			int32 frame = 7;
			if ((saveRAM->chaosEmeralds >> i) & 1)
				frame = i;
			self->emeraldsAnimator.frameID = frame;
			drawPos.y                      = self->emeraldPositions[i];
			RSDK.DrawSprite(&self->emeraldsAnimator, &drawPos, true);
			drawPos.x += 0x200000;
		}
	}

	drawPos.x    = self->messagePos2.x;
	drawPos.y    = self->messagePos2.y;
	drawPos.x    = centerX + 2 * drawPos.x;
	vertPos[0].x = drawPos.x - 0x740000;
	vertPos[0].y = drawPos.y - 0x140000;
	vertPos[1].x = 0x680000 + drawPos.x;
	vertPos[2].x = 0x780000 + drawPos.x;
	vertPos[3].x = drawPos.x - 0x640000;
	vertPos[1].y = drawPos.y - 0x140000;
	vertPos[2].y = drawPos.y - 0x40000;
	vertPos[3].y = drawPos.y - 0x40000;
	RSDK.DrawFace(vertPos, 4, 0x00, 0x00, 0x00, 0xFF, INK_NONE);

	if (self->messageType > SC_MSG_SPECIALCLEAR) {
		drawPos.x    = self->messagePos1.x;
		drawPos.y    = self->messagePos1.y;
		drawPos.x    = centerX + 2 * drawPos.x;
		vertPos[0].x = drawPos.x - 0x740000;
		vertPos[0].y = drawPos.y + 0x1C0000;
		vertPos[1].x = 0x680000 + drawPos.x;
		vertPos[2].x = 0x780000 + drawPos.x;
		vertPos[3].x = drawPos.x - 0x640000;
		vertPos[1].y = drawPos.y + 0x1C0000;
		vertPos[2].y = drawPos.y + 0x2C0000;
		vertPos[3].y = drawPos.y + 0x2C0000;
		RSDK.DrawFace(vertPos, 4, 0x00, 0x00, 0x00, 0xFF, INK_NONE);
	}

	drawPos.x = self->messagePos1.x;
	drawPos.y = self->messagePos1.y;
	drawPos.x += centerX;
	switch (self->messageType) {
		case SC_MSG_SPECIALCLEAR:
			self->playerNameAnimator.frameID = 0;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
			break;

		case SC_MSG_GOTEMERALD:
			self->playerNameAnimator.frameID = 1;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			self->playerNameAnimator.frameID = 2;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			drawPos.x = self->messagePos2.x;
			drawPos.y = self->messagePos2.y;
			drawPos.x += centerX;
			if (UFO_Setup) {
				self->playerNameAnimator.frameID = 3;
				RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
			} else {
				SpecialClearStaticExt.SEAnimator.frameID = 0;
				RSDK.DrawSprite(&SpecialClearStaticExt.SEAnimator, &drawPos, true);
			}
			break;

		case SC_MSG_ALLEMERALDS:
			self->playerNameAnimator.frameID = 4;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			self->playerNameAnimator.frameID = 5;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			drawPos.x = self->messagePos2.x;
			drawPos.y = self->messagePos2.y;
			drawPos.x += centerX;
			if (UFO_Setup) {
				self->playerNameAnimator.frameID = 6;
				RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
			} else {
				SpecialClearStaticExt.SEAnimator.frameID = 1;
				RSDK.DrawSprite(&SpecialClearStaticExt.SEAnimator, &drawPos, true);
			}
			break;

		case SC_MSG_SUPER:
			self->playerNameAnimator.frameID = 7;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			self->playerNameAnimator.frameID = 8;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			self->playerNameAnimator.frameID = 9;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			drawPos.x = self->messagePos2.x;
			drawPos.y = self->messagePos2.y;
			drawPos.x += centerX;
			self->playerNameAnimator.frameID = 10;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			if (UFO_Setup) {
				self->playerNameAnimator.frameID = 11;
			} else {
				self->playerNameAnimator.frameID = 12;
			}
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

			self->playerNameAnimator.frameID = 13;
			RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);
			break;

		default: break;
	}
	drawPos.x = self->scoreBonusPos.x;
	drawPos.y = self->scoreBonusPos.y;
	drawPos.x += centerX - 0x560000;
	self->bonusAnimator.frameID = 4;
	RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

	self->bonusAnimator.frameID = 6;
	drawPos.x += 0x660000;
	RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

	drawPos.x += 0x430000;
	SpecialClear_DrawNumbers(&drawPos, self->score);

	drawPos.x = self->ringBonusPos.x;
	drawPos.y = self->ringBonusPos.y;
	drawPos.x += centerX - 0x560000;
	self->bonusAnimator.frameID = 0;
	RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

	drawPos.x += 3276800;
	self->bonusAnimator.frameID = 3;
	RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

	self->bonusAnimator.frameID = 6;
	drawPos.x += 3407872;
	RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

	drawPos.x += 0x430000;
	SpecialClear_DrawNumbers(&drawPos, self->ringBonus);

	if (self->isBSS) {
		drawPos.x = self->perfectBonusPos.x;
		drawPos.y = self->perfectBonusPos.y;
		drawPos.x += centerX - 0x560000;
		self->bonusAnimator.frameID = 1;
		RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

		drawPos.x += 0x320000;
		self->bonusAnimator.frameID = 3;
		RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

		self->bonusAnimator.frameID = 6;
		drawPos.x += 0x340000;
		RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

		drawPos.x += 0x430000;
		SpecialClear_DrawNumbers(&drawPos, self->perfectBonus);
	} else {
		drawPos.x = self->machBonusPos.x;
		drawPos.y = self->machBonusPos.y;
		drawPos.x += centerX - 0x560000;
		self->bonusAnimator.frameID = 2;
		RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

		drawPos.x += 0x320000;
		self->bonusAnimator.frameID = 3;
		RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

		self->bonusAnimator.frameID = 6;
		drawPos.x += 0x340000;
		RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

		drawPos.x += 0x430000;
		SpecialClear_DrawNumbers(&drawPos, self->machBonus);
	}

	if (self->hasContinues) {
		drawPos.x = self->continuePos.x;
		drawPos.y = self->continuePos.y;
		drawPos.x += centerX - 0x560000;
		self->bonusAnimator.frameID = 5;
		RSDK.DrawSprite(&self->bonusAnimator, &drawPos, true);

		if (self->continueIconVisible) {
			drawPos.x += 0xB00000;
			drawPos.y += 0xA0000;
			RSDK.DrawSprite(&self->continueAnimator, &drawPos, true);
		}
	}

	if (self->showFade)
		RSDK.FillScreen(self->fillColor, self->timer, self->timer - 128, self->timer - 256);
}

void SpecialClear_State_SetupDelay() {
	RSDK_THIS(SpecialClear);

	if (self->timer <= 0) {
		self->timer    = 0;
		self->showFade = false;
		self->state    = SpecialClear_State_EnterText;

		Music_PlayTrack(TRACK_ACTCLEAR);
	} else {
		self->timer -= 16;
	}
}