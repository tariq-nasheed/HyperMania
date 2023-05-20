#include "HPZEmerald.h"

ObjectHPZEmerald *HPZEmerald;
int32 counter;

void HPZEmerald_Update_Hook(void) {
	Mod.Super(HPZEmerald->classID, SUPER_UPDATE, NULL);
	RSDK_THIS(HPZEmerald);

	if (!HPZSetup) return;
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
				player->controlLock = 1;
				if (counter == 0) player->groundVel = 0;
				++counter;
				if (counter == 0x1F) {
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

	RSDK.SetActivePalette(6, 0, ScreenInfo->size.y);
	RSDK.DrawSprite(&ext->animator, NULL, false);
	RSDK.ProcessAnimation(&ext->animator);
	RSDK.SetActivePalette(0, 0, ScreenInfo->size.y);
}

void HPZEmerald_Create_Hook(void* data) {
	Mod.Super(HPZEmerald->classID, SUPER_CREATE, data);
	RSDK_THIS(HPZEmerald);

	if (self->type == HPZEMERALD_MASTER) {
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
	counter = 0;
	Mod.Super(HPZEmerald->classID, SUPER_STAGELOAD, NULL);
	HPZEmeraldStaticExt.sfxSpecialWarp = RSDK.GetSfx("Global/SpecialWarp.wav");
	HPZEmeraldStaticExt.aniFrames = RSDK.LoadSpriteAnimation("HPZ/Emerald.bin", SCOPE_STAGE);
}
