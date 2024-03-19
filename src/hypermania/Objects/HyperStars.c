#include "HyperStars.h"
#include "Player.h"
#include "Zone.h"

ObjectHyperStars* HyperStars;

// Standard Entity Events
void HyperStars_Update(void) {
	RSDK_THIS(HyperStars);
	if (!self->player) return;
	if (!Player_IsHyper(self->player)) {
		destroyEntity(self);
		return;
	}

	for (int32 i = 0; i != HYPERSTARS_COUNT; ++i) {
		if (self->instanceTimer[i] < 0) {
			++self->instanceTimer[i];
			if (self->instanceTimer[i] != 0) continue;
			RSDK.ProcessAnimation(&self->instanceAnimator[i]);
		}

		++self->instanceTimer[i];
		RSDK.ProcessAnimation(&self->instanceAnimator[i]);
		if (self->instanceAnimator[i].frameID >= 3) {
			RSDK.SetSpriteAnimation(HyperStars->aniFrames, 0, &self->instanceAnimator[i], true, 0);
			self->instanceVel[i].x = 0;
			self->instanceVel[i].y = 0;
			RSDK.ProcessAnimation(&self->instanceAnimator[i]);
			self->instanceTimer[i] = 0;
		}
		self->instanceVel[i].x += RSDK.Sin256(self->instanceOsc[i]) << 11;
		self->instanceVel[i].y += RSDK.Cos256(self->instanceOsc[i]) << 11;
		self->instancePos[i].x = self->player->position.x + self->instanceVel[i].x * (self->player->direction & FLIP_X ? -1 : 1);
		self->instancePos[i].y = self->player->position.y + self->instanceVel[i].y;
		self->instanceOsc[i] -= 0x10;
	}

	self->drawGroup = self->player->drawGroup;
}

void HyperStars_LateUpdate(void) {}
void HyperStars_StaticUpdate(void) {}

void HyperStars_Draw(void) {
	RSDK_THIS(HyperStars);
	if (!self->player || !self->player->visible) return;

	if (self->player->isChibi) {
		self->drawFX |= FX_SCALE;
		self->scale.x = 0x100;
		self->scale.y = 0x100;
	} else {
		if (self->player->drawFX & FX_SCALE)
			self->drawFX |= FX_SCALE;
		else
			self->drawFX &= ~FX_SCALE;
		self->scale.x = self->player->scale.x;
		self->scale.y = self->player->scale.y;
	}

	for (int32 i = 0; i != HYPERSTARS_COUNT; ++i) {
		if (self->instanceTimer[i] < 0) continue;
		self->alpha = 0x100 - self->instanceTimer[i] * 6;
		RSDK.DrawSprite(&self->instanceAnimator[i], &self->instancePos[i], false);
	}
}


void HyperStars_Create(void* data) {
	RSDK_THIS(HyperStars);
	self->visible   = true;
	self->drawFX    = FX_FLIP;
	self->inkEffect = INK_ADD;
	self->alpha     = 0x100;
	self->active    = ACTIVE_NORMAL;

	if (data && ((Entity*)data)->classID == Player->classID) {
		self->player = (EntityPlayer*)data;
		self->position.x = self->player->position.x;
		self->position.y = self->player->position.y;
	}

	const int32 osc_add = 0x100 / HYPERSTARS_COUNT;
	for (int32 i = 0; i != HYPERSTARS_COUNT; ++i) {
		self->instanceOsc[i] = i * osc_add;
		self->instanceTimer[i] = -i - 1;
		RSDK.SetSpriteAnimation(HyperStars->aniFrames, 0, &self->instanceAnimator[i], true, 0);
	}
}

void HyperStars_StageLoad(void) {
	HyperStars->aniFrames = RSDK.LoadSpriteAnimation("Global/HyperSparkle.bin", SCOPE_STAGE);
}

void HyperStars_EditorDraw(void) {}
void HyperStars_EditorLoad(void) {}
void HyperStars_Serialize(void) {}
