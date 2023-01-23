#include "HPZIntro.h"
#include "HPZEmerald.h"
#include "HPZBeam.h"

ObjectHPZIntro* HPZIntro;

Entity* SortedSuperEmeralds[7];

color idk1[36];
color idk2[36] = { 0xA00000, 0xB01820, 0xC03040, 0xD04860, 0xE06080, 0x4040C8, 0x5858C8, 0xE060E0, 0x7070C8, 0x8888C8, 0xA0A0C8, 0xC048C8,
            0xA030B0, 0x801898, 0x600080, 0x88B8E0, 0x80E0,   0x2890E0, 0x58A8E0, 0xB8D0E0, 0x208000, 0x409800, 0x60B000, 0x80C800,
            0xA0E000, 0xE0E0A0, 0xD0C878, 0xC0B050, 0xB09828, 0xA08000, 0x808080, 0x909090, 0xA0A0A0, 0xC0C0C0, 0xB0B0B0, 0xE8E8E8 };
int32 emeraldStopAngle[7] = { 0x80, 0x86, 0x7a, 0x8c, 0x74, 0x92, 0x6e };
Vector2 emeraldFlyVector[7] = {
	(Vector2){ 0,    -1024 },
	(Vector2){ -248, -992 },
	(Vector2){ 248,  -992 },
	(Vector2){ -480, -900 },
	(Vector2){ 480,  -900 },
	(Vector2){ -684, -756 },
	(Vector2){ 684,  -756 }
};


void HPZIntro_Update(void) {
	RSDK_THIS(HPZIntro);

	if (HM_global.currentSave->transferedEmeralds == 0b01111111) {
		self->timer = 544;
		self->beams = 8;
	}

	++self->timer;
	if (self->timer == HPZ_TRANSFER_DELAY) {
		RSDK.PlaySfx(HPZIntro->sfxTwinkle, false, 0xFF);
	}

	if (self->timer >= 543 && self->beams != 8) {
		const int32 target_beams = (self->timer - 543) / 31 + 1;
		if (self->beams != target_beams) {
			self->beams = target_beams;
			if (self->beams < 8) {
				EntityPlayer* player = (EntityPlayer*)RSDK_GET_ENTITY_GEN(0);
				int32 spawn_y = Zone->playerBoundsT[0] - 0x8000;
				EntityHPZBeam* beam = CREATE_ENTITY(HPZBeam, NULL, SortedSuperEmeralds[self->beams - 1]->position.x, spawn_y);
				beam->target_y = SortedSuperEmeralds[self->beams - 1]->position.y;

				//RSDK_GET_ENTITY_GEN(0)->position.x = SortedSuperEmeralds[self->beams - 1]->position.x;
			}
		}
		if (self->beams == 8) {
			printf("done :)\n");
		}
	}
}

void HPZIntro_LateUpdate(void) {}
void HPZIntro_StaticUpdate(void) {}

void HPZIntro_Draw(void) {
	RSDK_THIS(HPZIntro);
	if (self->beams == 8) return;
	if (self->timer >= HPZ_TRANSFER_DELAY) {
		for (int32 c = 0; c < 36; ++c) {
			idk1[c] = RSDK.GetPaletteEntry(0, c + 128);
			RSDK.SetPaletteEntry(0, c + 128, idk2[c]);
		}

		const int32 lifetime = (self->timer - HPZ_TRANSFER_DELAY);
		const int32 sparsity = MIN(lifetime * 16, 6144); // 384 frames
		const int32 height = MIN(lifetime * 0x8000, 0x3F8000); // 127 frames
		bool32 all_stopped = true;
		Vector2 pos;
		
		for (int32 i = 0; i != 7; ++i) {
			if (lifetime >= 384 && emeraldStopAngle[i] - (self->emeraldAngle[i] % 0xff) < 4 && emeraldStopAngle[i] - ((self->emeraldAngle[i] - 4) % 0xff) >= 4) {
				self->emeraldAngle[i] = emeraldStopAngle[i];
				// blegh
			} else {
				self->emeraldAngle[i] += 4;
				all_stopped = false;
			}
			pos.x = self->position.x + RSDK.Sin256(self->emeraldAngle[i]) * sparsity + self->emeraldOffset[i].x;
			pos.y = self->position.y + RSDK.Cos256(self->emeraldAngle[i]) * sparsity - height + self->emeraldOffset[i].y;
			if (self->flying_off) {
				self->emeraldOffset[i].x += emeraldFlyVector[i].x << 8;
				self->emeraldOffset[i].y += emeraldFlyVector[i].y << 8;
			}
			if (lifetime & 1) RSDK.DrawSprite(&self->animatorEmeralds[i], &pos, false);
		}

		if (all_stopped && !self->flying_off) {
			self->flying_off = true;
			RSDK.PlaySfx(HPZIntro->sfxEmeraldFlying, false, 0xFF);
			for (int32 i = 0; i != 7; ++i) {
				self->velocity = emeraldFlyVector[i];
			}
		}

		for (int32 c = 0; c < 36; ++c) {
			RSDK.SetPaletteEntry(0, c + 0x80, idk1[c]);
		}
	}
}

void HPZIntro_Create(void *data) {
	RSDK_THIS(HPZIntro);

	if (!SceneInfo->inEditor) {
		self->active        = ACTIVE_NORMAL;
		self->visible       = true;
		self->drawGroup     = Zone->objectDrawGroup[0];
		for (int32 i = 0; i != 7; ++i) {
			self->emeraldAngle[i] = i * 0x24;
			RSDK.SetSpriteAnimation(HPZIntro->aniFramesEmerald, 0, &self->animatorEmeralds[i], true, i);
		}
	}
}

void HPZIntro_StageLoad(void) {
	HPZIntro->sfxTwinkle = RSDK.GetSfx("Global/Twinkle.wav");
	HPZIntro->sfxEmeraldFlying = RSDK.GetSfx("LRZ/LittlePlanet.wav");
	HPZIntro->aniFramesEmerald = RSDK.LoadSpriteAnimation("Cutscene/Emeralds.bin", SCOPE_STAGE);
}

#if RETRO_INCLUDE_EDITOR
void HPZIntro_EditorDraw(void) {}
void HPZIntro_EditorLoad(void) {}
#endif

void HPZIntro_Serialize(void) {}
