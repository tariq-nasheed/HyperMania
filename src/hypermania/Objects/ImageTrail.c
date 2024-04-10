#include "ImageTrail.h"
#include "Player.h"
#include "Mania/Global/Zone.h"

ObjectImageTrail* ImageTrail;

void ImageTrail_Create_OVERLOAD(void* data) {
	Mod.Super(ImageTrail->classID, SUPER_CREATE, data);
	RSDK_THIS(ImageTrail);
	AllocExtMem(RSDK.GetEntitySlot(self), sizeof(ImageTrailExt));
}

void ImageTrail_Draw_OVERLOAD() {
	RSDK_THIS(ImageTrail);

	int32 alpha = 0x60 * self->baseAlpha >> 8;
	const int32 inc   = 0x40 / (IMAGETRAIL_TRACK_COUNT / 3);
	const int32 flicker_id = Zone->timer % 4;

	// extra after-image for hyper forms
	ImageTrailExt* ext = (ImageTrailExt*)GetExtMem(RSDK.GetEntitySlot(self));
	if (self->player && Player_IsHyper(self->player) && ext->stateVisible[0]) {
		if (ext->stateScale[0] != 0x200) {
			self->drawFX |= FX_SCALE;
			self->scale.x = ext->stateScale[0];
			self->scale.y = ext->stateScale[0];
		}
		self->rotation  = ext->stateRotation[0];
		self->direction = ext->stateDirection[0];
		self->inkEffect = INK_ADD;
		self->alpha = 0x3F;
		if (flicker_id == 3) {
			self->alpha = 0xFF;
			RSDK.DrawSprite(&ext->stateAnimator[0], &ext->statePos[0], false);
			self->inkEffect = INK_SUB;
		}
		RSDK.DrawSprite(&ext->stateAnimator[0], &ext->statePos[0], false);
		self->drawFX &= ~FX_SCALE;
	}

	for (int32 i = (IMAGETRAIL_TRACK_COUNT / 3); i >= 0; --i) {
		const int32 id = (i * 3) - (i - 1);
		if (!self->stateVisible[id]) continue;

		if (self->stateScale[id] != 0x200) {
			self->drawFX |= FX_SCALE;
			self->scale.x = self->stateScale[id];
			self->scale.y = self->stateScale[id];
		}
		self->alpha = alpha;
		alpha += inc;
		self->rotation  = self->stateRotation[id];
		self->direction = self->stateDirection[id];

		if (self->player && Player_IsHyper(self->player)) {
			self->inkEffect = INK_ADD;
			self->alpha = 0x3F;
			if (flicker_id == i) {
				self->alpha = 0xFF;
				RSDK.DrawSprite(&self->stateAnimator[id], &self->statePos[id], false);
				self->inkEffect = INK_SUB;
			}
		}
		RSDK.DrawSprite(&self->stateAnimator[id], &self->statePos[id], false);

		self->drawFX &= ~FX_SCALE;
	}
}

void ImageTrail_LateUpdate_OVERLOAD() {
	RSDK_THIS(ImageTrail);
	ImageTrailExt* ext = (ImageTrailExt*)GetExtMem(RSDK.GetEntitySlot(self));

	ext->statePos[0].x     = self->statePos[IMAGETRAIL_TRACK_COUNT - 1].x;
	ext->statePos[0].y     = self->statePos[IMAGETRAIL_TRACK_COUNT - 1].y;
	ext->stateRotation[0]  = self->stateRotation[IMAGETRAIL_TRACK_COUNT - 1];
	ext->stateScale[0]     = self->stateScale[IMAGETRAIL_TRACK_COUNT - 1];
	ext->stateDirection[0] = self->stateDirection[IMAGETRAIL_TRACK_COUNT - 1];
	ext->stateVisible[0]   = self->stateVisible[IMAGETRAIL_TRACK_COUNT - 1];
	memcpy(&ext->stateAnimator[0], &self->stateAnimator[IMAGETRAIL_TRACK_COUNT - 1], sizeof(Animator));

	Mod.Super(ImageTrail->classID, SUPER_LATEUPDATE, NULL);
}