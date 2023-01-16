#include "HPZEmerald.h"

ObjectHPZEmerald *HPZEmerald;
int32 counter;

void HPZEmerald_Update_Hook(void) {
	Mod.Super(HPZEmerald->classID, SUPER_UPDATE, NULL);
	RSDK_THIS(HPZEmerald);

	int32 handle = -1;
	for (int32 i = 0; i != 7; ++i) {
		if (HPZEmeraldExtra[i].owner == (Entity*)self) {
			handle = i;
			break;
		}
	}
	if (handle == -1 || HPZEmeraldExtra[handle].color == -1) return;

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
					SceneInfo->listPos += 7 + handle;
					RSDK.PlaySfx(HPZEmeraldStaticExt.sfxSpecialWarp, false, 0xFF);
					Zone_StartFadeOut(10, 0xF0F0F0);
					//Music_FadeOut(0.05);
				}
			}
		}
	}
}

void HPZEmerald_Draw_Hook(void) {
	Mod.Super(HPZEmerald->classID, SUPER_DRAW, NULL);
	RSDK_THIS(HPZEmerald);

	int32 handle = -1;
	for (int32 i = 0; i != 7; ++i) {
		if (HPZEmeraldExtra[i].owner == (Entity*)self) {
			handle = i;
			break;
		}
	}
	if (handle == -1) return;

	RSDK.SetActivePalette(6, 0, ScreenInfo->size.y);
	RSDK.DrawSprite(&HPZEmeraldExtra[handle].animator, NULL, false);
	RSDK.ProcessAnimation(&HPZEmeraldExtra[handle].animator);
	RSDK.SetActivePalette(0, 0, ScreenInfo->size.y);
}

void HPZEmerald_Create_Hook(void* data) {
	Mod.Super(HPZEmerald->classID, SUPER_CREATE, NULL);
	RSDK_THIS(HPZEmerald);

	for (int32 i = 0; i != 7; ++i) {
		if (SortedSuperEmeralds[i] == (Entity*)self) {
			HPZEmeraldExtra[i].owner = (Entity*)self;
			if (SceneInfo->listPos == 31) {
				HPZEmeraldExtra[i].color = i;
				RSDK.SetSpriteAnimation(HPZEmeraldStaticExt.aniFrames, i + 1, &HPZEmeraldExtra[i].animator, true, 0);
			} else {
				HPZEmeraldExtra[i].color = -1;
			}
			break;
		}
	}
}

void HPZEmerald_StageLoad_Hook(void) {
	counter = 0;
	Mod.Super(HPZEmerald->classID, SUPER_STAGELOAD, NULL);
	memset(HPZEmeraldExtra, 0, sizeof(HPZEmeraldExt) * 7);
	HPZEmeraldStaticExt.sfxSpecialWarp = RSDK.GetSfx("Global/SpecialWarp.wav");
	HPZEmeraldStaticExt.aniFrames = RSDK.LoadSpriteAnimation("HPZ/Emerald.bin", SCOPE_STAGE);
}