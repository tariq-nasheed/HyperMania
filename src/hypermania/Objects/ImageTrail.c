#include "ImageTrail.h"
#include "Player.h"
#include "Zone.h"

ObjectImageTrail* ImageTrail;

void ImageTrail_Draw_Hook(void) {
	RSDK_THIS(ImageTrail);

	int32 alpha = 0x60 * self->baseAlpha >> 8;
	const int32 inc   = 0x40 / (IMAGETRAIL_TRACK_COUNT / 3);
	const int32 flicker_id = Zone->timer % 3;

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