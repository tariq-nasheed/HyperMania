#include "HPZEmerald.h"

ObjectHPZEmerald *HPZEmerald;
int32 counter;

void HPZEmerald_Update_Hook(void) {
	Mod.Super(HPZEmerald->classID, SUPER_UPDATE, NULL);
	RSDK_THIS(HPZEmerald);

	if (!HPZSetup) return;
	HPZEmeraldExt* ext = (HPZEmeraldExt*)GetExtMem(RSDK.GetEntitySlot(self));
	if (!ext || ext->color == -1) return;

	Hitbox hitbawks;
	hitbawks.left = -16;
	hitbawks.top = -29;
	hitbawks.right = 16;
	hitbawks.bottom = -16;
	foreach_active(Player, player) {
		if (player->onGround == 1) {
			if (Player_CheckCollisionTouch(player, self, &hitbawks) == C_TOP) {
				player->controlLock = 1;
				if (counter == 0) player->groundVel = 0;
				++counter;
				if (counter == 0x1F) {
					RSDK.SetScene("Special Stage", "");
					SceneInfo->listPos += 7 + ext->color;
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
	if (!ext || ext->color == -1) {
		Mod.Super(HPZEmerald->classID, SUPER_DRAW, NULL);
		return;
	}

	RSDK.SetActivePalette(6, 0, ScreenInfo->size.y);
	RSDK.DrawSprite(&ext->animator, NULL, false);
	RSDK.ProcessAnimation(&ext->animator);
	RSDK.SetActivePalette(0, 0, ScreenInfo->size.y);
}

void HPZEmerald_Create_Hook(void* data) {
	Mod.Super(HPZEmerald->classID, SUPER_CREATE, NULL);
	RSDK_THIS(HPZEmerald);

	for (int32 i = 0; i != 7; ++i) {
		if (SortedSuperEmeralds[i] == (Entity*)self) {
			HPZEmeraldExt* ext = (HPZEmeraldExt*)AllocExtMem(RSDK.GetEntitySlot(self), sizeof(HPZEmeraldExt));
			if (!ext) return;
			ext->owner = (Entity*)self;
			if (localHM_SaveRam.transferedEmeralds & 1 << i || !HPZSetup) {
				ext->color = i;
				RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, super_emerald_lookup[i], &ext->animator, true, 0);
			} else {
				ext->color = -1;
			}
			break;
		}
	}
}

void HPZEmerald_StageLoad_Hook(void) {
	counter = 0;
	Mod.Super(HPZEmerald->classID, SUPER_STAGELOAD, NULL);
	HPZEmeraldStaticExt.sfxSpecialWarp = RSDK.GetSfx("Global/SpecialWarp.wav");
	HPZEmeraldStaticExt.aniFrames = RSDK.LoadSpriteAnimation("HPZ/Emerald.bin", SCOPE_STAGE);
}