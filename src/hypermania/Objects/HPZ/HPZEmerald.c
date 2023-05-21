#include "HPZEmerald.h"

ObjectHPZEmerald *HPZEmerald;
int32 counter;

color SuperEmeraldPalette[57] = {
	0xACF41C, 0x98E42C, 0x7CCC10, 0x5CA000, 0x2C8400, 0x184C28, 0x182828, 0x181020, 
	0xFCD830, 0xFCAC20, 0xFC8820, 0xE44000, 0xB80000, 0x800020, 0x3C002C, 0x20002C, 
	0x98C4FC, 0x74A0FC, 0x4C7CFC, 0x0044E4, 0x002CB8, 0x000088, 0x00005C, 0x000034, 
	0xFC84E4, 0xE864D4, 0xD034C4, 0x9810B0, 0x6C1898, 0x40106C, 0x280C38, 0x20082C, 
	0xC8E8E0, 0xB0D8D8, 0x98C0C8, 0x708C9C, 0x587090, 0x484868, 0x302040, 0x181020, 
	0xB8FCDC, 0x88F0E0, 0x88D4E0, 0x38ACE0, 0x1C80E0, 0x0060AC, 0x004074, 0x002440, 
	0xFC7CA4, 0xFC6090, 0xF04064, 0xBC0060, 0x900060, 0x540054, 0x38004C, 0x10002C,
	0xFCFCFC
};

void HPZEmerald_Update_Hook(void) {
	Mod.Super(HPZEmerald->classID, SUPER_UPDATE, NULL);
	RSDK_THIS(HPZEmerald);

	if (!HPZSetup || self->type == HPZEMERALD_MASTER) return;
	HPZEmeraldExt* ext = (HPZEmeraldExt*)GetExtMem(RSDK.GetEntitySlot(self));
	if (!ext || ext->type == -1 || HM_global.currentSave->superEmeralds & 1 << sonic3_emerald_lookup[super_emerald_lookup[ext->type]]) return;

	Hitbox hitbawks;
	hitbawks.left = -16;
	hitbawks.top = -29;
	hitbawks.right = 16;
	hitbawks.bottom = -16;
	foreach_active(Player, player) {
		if (!player->sidekick && player->onGround == 1) {
			if (Player_CheckCollisionTouch(player, self, &hitbawks) == C_TOP) {
				player->groundVel = 0;
				player->state = Player_State_Static;
				RSDK.SetSpriteAnimation(player->aniFrames, ANI_IDLE, &player->animator, false, 0);
				++counter;
				if (counter == 31) {
					RSDK.SetScene("Special Stage", "");
					SceneInfo->listPos += super_emerald_lookup[ext->type];
#if MANIA_USE_PLUS
					SceneInfo->listPos += 7;
#endif
					RSDK.PlaySfx(HPZEmeraldStaticExt.sfxSpecialWarp, false, 0xFF);
					Zone_StartFadeOut(10, 0xF0F0F0);
					Music_FadeOut(0.05);
				}
			}
		}
	}
}

void HPZEmerald_Draw_Hook(void) {
	RSDK_THIS(HPZEmerald);
	HPZEmeraldExt* ext = (HPZEmeraldExt*)GetExtMem(RSDK.GetEntitySlot(self));
	if (!ext || ext->type == -1) {
		Mod.Super(HPZEmerald->classID, SUPER_DRAW, NULL);
		return;
	}

	if (self->type != HPZEMERALD_MASTER) {
		RSDK.SetActivePalette(6, 0, ScreenInfo->size.y);
		RSDK.DrawSprite(&ext->animator, NULL, false);
		if (ext->animator.animationID > 0) ext->animator.frameID = Zone->timer & 1;
		RSDK.SetActivePalette(0, 0, ScreenInfo->size.y);
	} else {
		// ext->type gets reused as timer for master emerald
		if (!self->alpha && ext->type >= 0) {
			self->alpha = abs(RSDK.Sin256(ext->type * 1.25) >> 1);
			self->alpha >>= 1;
			Mod.Super(HPZEmerald->classID, SUPER_DRAW, NULL);
			self->alpha <<= 1;
			RSDK.DrawSprite(&self->emeraldAnimator, NULL, false);
			self->alpha = 0;
			++ext->type;
		} else {
			Mod.Super(HPZEmerald->classID, SUPER_DRAW, NULL);
		}
	}
}

void HPZEmerald_Create_Hook(void* data) {
	Mod.Super(HPZEmerald->classID, SUPER_CREATE, data);
	RSDK_THIS(HPZEmerald);

	if (self->type == HPZEMERALD_MASTER) {
		HPZEmeraldExt* ext = (HPZEmeraldExt*)AllocExtMem(RSDK.GetEntitySlot(self), sizeof(HPZEmeraldExt));
		if (HM_global.currentSave->superEmeralds == 0b01111111) {
			ext->type = 0;
		} else {
			ext->type = -1;
		}
		// you might think this is a misnomer but you'd be wrong! the master emerald IS technically a super emerald according to the japanese sonic jam guidebook! (https://twitter.com/chaotic_hog/status/1652734301702610946)
		SortedSuperEmeralds[7] = (Entity*)self;
	} else {
		for (int32 i = 0; i != 7; ++i) {
			if (SortedSuperEmeralds[i] == (Entity*)self) {
				HPZEmeraldExt* ext = (HPZEmeraldExt*)AllocExtMem(RSDK.GetEntitySlot(self), sizeof(HPZEmeraldExt));
				if (!ext) return;
				ext->owner = (Entity*)self;

				const int32 index = sonic3_emerald_lookup[super_emerald_lookup[i]];
				if (HM_global.currentSave->transferedEmeralds & 1 << index) {
					ext->type = i;
				}

				if (HM_global.currentSave->superEmeralds & 1 << index) {
					RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, index + 1, &ext->animator, true, 0);
				} else if (HM_global.currentSave->transferedEmeralds & 1 << index) {
					RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, 0, &ext->animator, true, 0);
				} else {
					ext->type = -1;
				}
				break;
			}
		}
	}
}

void HPZEmerald_StageLoad_Hook(void) {
	// to lazy to make this a .act file, plus it technically takes up less space so ermmmmmm yeah logic bomb
	for (int32 i = 0; i != 57; ++i) {
		RSDK.SetPaletteEntry(6, 128 + i, SuperEmeraldPalette[i]);
	}
	counter = 0;
	Mod.Super(HPZEmerald->classID, SUPER_STAGELOAD, NULL);
	HPZEmeraldStaticExt.sfxSpecialWarp = RSDK.GetSfx("Global/SpecialWarp.wav");
	HPZEmeraldStaticExt.aniFrames = RSDK.LoadSpriteAnimation("HPZ/Emerald.bin", SCOPE_STAGE);
}
