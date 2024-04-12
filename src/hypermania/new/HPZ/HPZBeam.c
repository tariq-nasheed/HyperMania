#include "HPZBeam.h"

ObjectHPZBeam* HPZBeam;

void HPZBeam_Update(void) {
	RSDK_THIS(HPZBeam);

	if (!self->hit_timer) {
		self->position.y += TO_FIXED(16);
		if (self->target_y <= self->position.y) {
			self->hit_timer = 1;
			Camera_ShakeScreen(RSDK.GetEntitySlot(0), 0, 8);
			RSDK.PlaySfx(HPZBeam->sfxImpact, false, 0xFF);

			// FUCKING STUPID
			for (int32 i = 0; i != 7; ++i) {
				Entity* emerald = SortedSuperEmeralds[i];
				if (emerald && emerald->position.x == self->position.x && emerald->position.y > self->position.y - TO_FIXED(16)) {
					RSDK.PlaySfx(HPZBeam->sfxLedgeBreak, false, 0xFF);
					HPZEmeraldExt* ext = (HPZEmeraldExt*)GetExtMem(RSDK.GetEntitySlot(emerald));
					ext->type = i;
					emerald->alpha = 0xFF;
					RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, 0, &ext->animator, true, 0);
					HM_globals->currentSave->transferedEmeralds |= 1 << i; 

					// da breeze
					EntityDebris* debris;

					debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, emerald->position.x, emerald->position.y);
					RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, 8, &debris->animator, true, 0);
					debris->drawGroup       = Zone->objectDrawGroup[1];
					debris->velocity.x      = -0x20000;
					debris->velocity.y      = -0x40000;
					debris->gravityStrength = 0x4800;

					debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, emerald->position.x, emerald->position.y);
					RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, 8, &debris->animator, true, 1);
					debris->drawGroup       = Zone->objectDrawGroup[1];
					debris->velocity.x      = 0x20000;
					debris->velocity.y      = -0x40000;
					debris->gravityStrength = 0x4800;

					debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, emerald->position.x, emerald->position.y);
					RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, 8, &debris->animator, true, 2);
					debris->drawGroup       = Zone->objectDrawGroup[1];
					debris->velocity.x      = -0x10000;
					debris->velocity.y      = -0x20000;
					debris->gravityStrength = 0x4800;

					debris = CREATE_ENTITY(Debris, Debris_State_FallAndFlicker, emerald->position.x, emerald->position.y);
					RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, 8, &debris->animator, true, 3);
					debris->drawGroup       = Zone->objectDrawGroup[1];
					debris->velocity.x      = 0x10000;
					debris->velocity.y      = -0x20000;
					debris->gravityStrength = 0x4800;

					break;
				}
			}
		}
	} else {
		++self->hit_timer;
		if (self->hit_timer >= 31) self->top += 0x100000;
		if (self->top >= self->position.y) destroyEntity(self);
	}
	RSDK.ProcessAnimation(&self->topAnimator);
	RSDK.ProcessAnimation(&self->middleAnimator);
	RSDK.ProcessAnimation(&self->bottomAnimator);
}

void HPZBeam_LateUpdate(void) {}
void HPZBeam_StaticUpdate(void) {}

void HPZBeam_Draw(void) {
	RSDK_THIS(HPZBeam);
	self->alpha = (Zone->timer & 1) ? 0x7F : 0xFF;

	Vector2 drawpos = self->position;
	drawpos.y = self->top - 0x80000;
	RSDK.DrawSprite(&self->topAnimator, &drawpos, false);

	for (int32 i = self->top; i < self->position.y; i += 0x100000) {
		drawpos.y = i;
		RSDK.DrawSprite(&self->middleAnimator, &drawpos, false);
	}
	drawpos.y += 0x80000;
	RSDK.DrawSprite(&self->bottomAnimator, &drawpos, false);

}

void HPZBeam_Create(void *data) {
	RSDK_THIS(HPZBeam);

	self->visible   = true;
	self->drawGroup = Zone->objectDrawGroup[1];
	self->active    = ACTIVE_NORMAL;
	self->inkEffect = INK_ALPHA;

	self->top = self->position.y;
	RSDK.SetSpriteAnimation(HPZBeam->aniFrames, 0, &self->topAnimator, true, 0);
	RSDK.SetSpriteAnimation(HPZBeam->aniFrames, 1, &self->middleAnimator, true, 0);
	RSDK.SetSpriteAnimation(HPZBeam->aniFrames, 2, &self->bottomAnimator, true, 0);
}

void HPZBeam_StageLoad(void) {
	HPZBeam->sfxImpact     = RSDK.GetSfx("Stage/BeamImpact.wav");
	HPZBeam->sfxLedgeBreak = RSDK.GetSfx("Stage/LedgeBreak.wav");
	HPZBeam->aniFrames = RSDK.LoadSpriteAnimation("HPZ/WarpBeam.bin", SCOPE_STAGE);
}

void HPZBeam_EditorDraw(void) {}
void HPZBeam_EditorLoad(void) {}

void HPZBeam_Serialize(void) {}
