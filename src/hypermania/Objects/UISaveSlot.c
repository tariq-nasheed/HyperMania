#include "UISaveSlot.h"

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
	Mod.Super(UISaveSlot->classID, SUPER_DRAW, NULL);
	RSDK_THIS(UISaveSlot);

	if (self->type == UISAVESLOT_REGULAR && !self->isNewSave) {
		Vector2 drawPos;
		drawPos.y = 0x450000 + self->position.y;
		HM_SaveRAM* save = ((UISaveSlotExt*)GetExtMem(RSDK.GetEntitySlot(self)))->save;

		for (int32 i = 0; i < 7; ++i) {
			drawPos.x = self->position.x - 0x240000 + 0xC0000 * i;
			if (save->transferedEmeralds & 1 << i) {
				UISaveSlotStaticExt.SEAnimator.frameID = (save->superEmeralds & 1 << i) ? i + 1 : 8;
				if (UISaveSlotStaticExt.SEAnimator.frameID != 8 && timer & 1) {
					UISaveSlotStaticExt.SEAnimator.frameID = 0;
				}
				RSDK.DrawSprite(&UISaveSlotStaticExt.SEAnimator, &drawPos, false);
			}
		}
	}
}