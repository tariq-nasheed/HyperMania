#include "JetGlideEffect.h"

ObjectJetGlideEffect* JetGlideEffect;

void JetGlideEffect_Update() {
	RSDK_THIS(JetGlideEffect);
	++self->timer;
	if (self->timer > 32) destroyEntity(self);
}

void JetGlideEffect_LateUpdate() {}

void JetGlideEffect_StaticUpdate() {}

void JetGlideEffect_Draw() {
	RSDK_THIS(JetGlideEffect);

	int32 rndIndex = self->rndOffset;
	int32 rndIndex2 = self->rndOffset2;
	if (self->timer >= 12) {
		for (int32 i = 0; i != self->sparkleCount; ++i) {
			RSDK.SetSpriteAnimation(JetGlideEffect->aniFrames, self->rndTable[rndIndex] % 4, &self->animator, true, 0);
			rndIndex = (rndIndex + 1) % 256;
			int32 loops = 0;
			self->animator.frameID = (self->timer - 12) >> 1;
			while (self->animator.frameID >= self->animator.frameCount) {
				++loops;
				self->animator.frameID -= self->animator.frameCount;
			}

			Vector2 pos = self->position;
			pos.x += self->rndTable[rndIndex2] * 4 * 12 + self->rndTable[rndIndex2] * 1 * self->timer;
			rndIndex2 = (rndIndex2 + 1) % 256;
			pos.y += self->rndTable[rndIndex2] * 4 * 12 + self->rndTable[rndIndex2] * 1 * self->timer;
			rndIndex2 = (rndIndex2 + 1) % 256;
			if (loops < 2) RSDK.DrawSprite(&self->animator, &pos, false);
		}
	}

	rndIndex = self->rndOffset;
	if (self->timer <= 16) {
		RSDK.SetSpriteAnimation(JetGlideEffect->aniFrames, 4, &self->animator, true, 0);
		self->animator.frameID = 0;
		for (int32 i = 0; i != self->dustCount; ++i) {
			Vector2 pos = self->position;
			int32 vel = self->rndTable[rndIndex] * 8;
			int32 offset = vel;
			for (int32 l = 0; l != self->timer; ++l) {
				vel *= 0.95;
				offset += vel;
			}
			pos.x += offset;
			rndIndex = (rndIndex + 1) % 256;

			vel = self->rndTable[rndIndex] * 8;
			offset = vel;
			for (int32 l = 0; l != self->timer; ++l) {
				vel *= 0.95;
				offset += vel;
			}
			pos.y += offset;
			rndIndex = (rndIndex + 1) % 256;
			RSDK.DrawSprite(&self->animator, &pos, false);
		}
	}
}

void JetGlideEffect_Create(void* data) {
	RSDK_THIS(JetGlideEffect);
	self->visible   = true;
	self->drawFX    = FX_NONE;
	self->active    = ACTIVE_NORMAL;

	self->dustCount    = RSDK.Rand(125, 150);
	self->sparkleCount = RSDK.Rand(20, 30);
	self->rndOffset = RSDK.Rand(0, 255);
	self->rndOffset2 = RSDK.Rand(0, 255);
	for (int32 i = 0; i != 256; ++i) {
		self->rndTable[i] = RSDK.Rand(-0xFFFF, 0xFFFF);
	}
	RSDK.SetSpriteAnimation(JetGlideEffect->aniFrames, 0, &self->animator, true, 0);
}

void JetGlideEffect_StageLoad() {
	JetGlideEffect->aniFrames = RSDK.LoadSpriteAnimation("Global/RaySparkle.bin", SCOPE_STAGE);
}

#if RETRO_INCLUDE_EDITOR
void JetGlideEffect_EditorDraw() {}

void JetGlideEffect_EditorLoad() {}
#endif

void JetGlideEffect_Serialize() {}