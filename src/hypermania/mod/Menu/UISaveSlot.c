#include "UISaveSlot.h"

void (*UIWidgets_DrawRectOutline_Black)(int32 x, int32 y, int32 width, int32 height);
void (*UIWidgets_DrawRectOutline_Blended)(int32 x, int32 y, int32 width, int32 height);
void (*UIWidgets_DrawRectOutline_Flash)(int32 x, int32 y, int32 width, int32 height);
void (*UIWidgets_DrawRightTriangle)(int32 x, int32 y, int32 size, int32 red, int32 green, int32 blue);
void (*UIWidgets_DrawUpDownArrows)(int32 x, int32 y, int32 arrowDist);
void (*UISaveSlot_DrawPlayerIcons)(int32 drawX, int32 drawY);
void (*UISaveSlot_DrawPlayerInfo)(int32 drawX, int32 drawY);
void (*UISaveSlot_State_Selected)();

ObjectUISaveSlot *UISaveSlot;
UISaveSlotStaticExt_t UISaveSlotStaticExt;
static int32 timer; // dumb

void UISaveSlot_StageLoad_OVERLOAD() {
	Mod.Super(UISaveSlot->classID, SUPER_STAGELOAD, NULL);
	UISaveSlotStaticExt.SEAniFrames = RSDK.LoadSpriteAnimation("UI/SaveSelectSE.bin", SCOPE_STAGE);
	RSDK.SetSpriteAnimation(UISaveSlotStaticExt.SEAniFrames, 0, &UISaveSlotStaticExt.SEAnimator, true, 0);
	timer = 0;
}

void UISaveSlot_StaticUpdate_OVERLOAD() {
	Mod.Super(UISaveSlot->classID, SUPER_STATICUPDATE, NULL);
	++timer;
}

void UISaveSlot_Create_OVERLOAD(void* data) {
	Mod.Super(UISaveSlot->classID, SUPER_CREATE, data);
	RSDK_THIS(UISaveSlot);

#if MANIA_USE_PLUS
	((UISaveSlotExt*)AllocExtMem(RSDK.GetEntitySlot(self), sizeof(UISaveSlotExt*)))->save = HM_Save_GetDataPtr(self->slotID, self->encoreMode);
#else
	((UISaveSlotExt*)AllocExtMem(RSDK.GetEntitySlot(self), sizeof(UISaveSlotExt*)))->save = HM_Save_GetDataPtr(self->slotID, false);
#endif
}

void UISaveSlot_Draw_OVERLOAD() {
	// have to overload this completely to fix the "super emeralds rendering while screen is black" bug
	// plus it might open up more options for us later on, yippe!
	RSDK_THIS(UISaveSlot);

	Vector2 drawPos;
	if (self->type == UISAVESLOT_REGULAR) {
		drawPos.y = self->position.y + 0x30000;
		drawPos.x = self->position.x + 0x30000;
		RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y - 0x4F0000, 0x600000, 0xA40000, 0xFFFFFF, 127, INK_BLEND, false);

		drawPos.x = self->position.x - 0x2D0000;
		drawPos.y = self->position.y - 0x100000;
		UIWidgets_DrawRightTriangle(drawPos.x, drawPos.y, (self->textBounceOffset >> 11), 232, 40, 88);

		drawPos.x = self->position.x + 0x2D0000;
		drawPos.y = 0x4F0000 + self->position.y;
		UIWidgets_DrawRightTriangle(drawPos.x, drawPos.y, (-64 * self->textBounceOffset) >> 16, 0x60, 0xA0, 0xB0);
		UIWidgets_DrawRightTriangle(drawPos.x, drawPos.y, (-44 * self->textBounceOffset) >> 16, 0x58, 0x70, 0xE0);

		drawPos.x = self->position.x + 0x30000;
		drawPos.y = self->position.y + 0x30000;
		UIWidgets_DrawRectOutline_Blended(drawPos.x, drawPos.y, 96, 164);

		RSDK.DrawRect(drawPos.x - 0x2D0000, drawPos.y - 0x130000, 0x5A0000, 0x30000, 0x000000, 0xFF, INK_BLEND, false);

		if (self->isSelected) {
			UIWidgets_DrawRectOutline_Flash(self->position.x, self->position.y, 96, 164);
		} else {
			UIWidgets_DrawRectOutline_Black(self->position.x, self->position.y, 96, 164);
		}

		self->uiAnimator.frameID = 0;
		drawPos.x                = self->position.x;
		drawPos.y                = self->position.y - 0x300000;
		RSDK.DrawSprite(&self->uiAnimator, &drawPos, false);

		if (self->isNewSave || self->saveZoneID == 0xFF) {
			RSDK.DrawSprite(&self->iconBGAnimator, &drawPos, false);
			RSDK.DrawSprite(&self->saveStatusAnimator, &drawPos, false);
		}
		else if ((self->isSelected || self->state == UISaveSlot_State_Selected) && self->saveZoneID <= ZONE_COUNT_SAVEFILE) {
			SpriteFrame *frame = RSDK.GetFrame(UISaveSlot->aniFrames, 5, self->saveZoneID);
			frame->pivotX      = -43;
			frame->width       = 86;
			frame->sprX        = self->zoneIconSprX;

			if (frame->sprX > 106) {
				int32 width  = frame->sprX - 106;
				frame->width = 86 - width;
				RSDK.DrawSprite(&self->zoneIconAnimator, &drawPos, false);

				frame->pivotX += frame->width;
				frame->sprX  = 0;
				frame->width = width;
			}

			RSDK.DrawSprite(&self->zoneIconAnimator, &drawPos, false);
			RSDK.DrawSprite(&self->zoneNameAnimator, &drawPos, false);
		}
		else {
			self->drawFX = FX_FLIP;
			RSDK.DrawSprite(&self->fuzzAnimator, &drawPos, false);

			self->drawFX = FX_NONE;
			RSDK.DrawSprite(&self->zoneNameAnimator, &drawPos, false);
		}

		if (self->isNewSave) {
			drawPos.x = self->position.x;
			drawPos.y = self->position.y + 0x200000;
			UISaveSlot_DrawPlayerIcons(drawPos.x, drawPos.y);
		}
		else {
			RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y + 0x3D0000, 0x5A0000, 0x100000, 0x000000, 0xFF, INK_NONE, false);

			HM_SaveRAM* save = ((UISaveSlotExt*)GetExtMem(RSDK.GetEntitySlot(self)))->save;
			drawPos.x = self->position.x - 0x240000;
			drawPos.y = 0x450000 + self->position.y;
			for (int32 i = 0; i < 7; ++i) {
				if (save->transferedEmeralds & 1 << i) {
					UISaveSlotStaticExt.SEAnimator.frameID = (save->superEmeralds & 1 << i) ? i + 1 : 8;
					if (UISaveSlotStaticExt.SEAnimator.frameID != 8 && timer & 1) {
						UISaveSlotStaticExt.SEAnimator.frameID = 0;
					}
					RSDK.DrawSprite(&UISaveSlotStaticExt.SEAnimator, &drawPos, false);
				} else {
					self->emeraldsAnimator.frameID = ((1 << i) & self->saveEmeralds) ? i : 7;
					RSDK.DrawSprite(&self->emeraldsAnimator, &drawPos, false);
				}
				drawPos.x += 0xC0000;
			}

			drawPos.x = self->position.x;
			drawPos.y = self->position.y + 0x100000;
#if MANIA_USE_PLUS
			if (!self->encoreMode || self->type == UISAVESLOT_NOSAVE) {
				if (!self->saveContinues) {
					drawPos.y += 0x20000;
				}
				drawPos.y += 0x20000;
			}
			else
				drawPos.y += 0x80000;
#else
			if (self->type == UISAVESLOT_NOSAVE)
				drawPos.y += 0x20000;
			else
				drawPos.y += 0x80000;
#endif
			UISaveSlot_DrawPlayerIcons(drawPos.x, drawPos.y);

			drawPos.x = self->position.x;
			drawPos.y = self->position.y + 0x330000;
			UISaveSlot_DrawPlayerInfo(drawPos.x, drawPos.y);
		}
	}
	else {
		drawPos.y = self->position.y + 0x30000;
		drawPos.x = self->position.x + 0x30000;
		RSDK.DrawRect(self->position.x - 0x2D0000, self->position.y - 0x1F0000, 0x600000, 0x440000, 0xFFFFFF, 0x7F, INK_BLEND, false);

		drawPos.x = self->position.x + 0x30000;
		drawPos.y = self->position.y + 0x30000;
		UIWidgets_DrawRectOutline_Blended(drawPos.x, drawPos.y, 96, 68);

		self->uiAnimator.frameID = 1;
		RSDK.DrawSprite(&self->uiAnimator, NULL, false);

		drawPos = self->position;
		UISaveSlot_DrawPlayerIcons(self->position.x, self->position.y);
		RSDK.DrawSprite(&self->zoneNameAnimator, NULL, false);
	}

	if (self->isSelected || self->type == UISAVESLOT_REGULAR) {
		if (self->type == UISAVESLOT_NOSAVE)
			UIWidgets_DrawRectOutline_Flash(self->position.x, self->position.y, 96, 68);

		if (self->isSelected && !(self->zoneIconSprX & 8)) {
			drawPos.x = self->position.x;
			drawPos.y = self->position.y;
#if MANIA_USE_PLUS
			if (!self->encoreMode) {
#endif
				if (self->type == UISAVESLOT_NOSAVE) {
					drawPos.y -= 0x60000;
					UIWidgets_DrawUpDownArrows(drawPos.x, drawPos.y, 40);
				}
				else if (self->isNewSave) {
					drawPos.y += 0x200000;
					UIWidgets_DrawUpDownArrows(drawPos.x, drawPos.y, 64);
				}
				else if (self->listID == 1) {
					drawPos.y -= 0x300000;
					UIWidgets_DrawUpDownArrows(drawPos.x, drawPos.y, 40);
				}
#if MANIA_USE_PLUS
			}
			else if (self->listID == 1) {
				drawPos.y -= 0x300000;
				UIWidgets_DrawUpDownArrows(drawPos.x, drawPos.y, 40);
			}
#endif
		}
	}

	RSDK.DrawCircle(ScreenInfo->center.x, ScreenInfo->center.y, self->fxRadius, 0x000000, self->alpha, INK_ALPHA, true);
}