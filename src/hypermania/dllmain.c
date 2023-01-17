#include "../GameAPI/C/GameAPI/Game.h"

#include "util.h"

// game classes litte/no notable modifications
#include "Objects/Boilerplate/Animals.h"
#include "Objects/Boilerplate/Camera.h"
#include "Objects/Boilerplate/CollapsingPlatform.h"
#include "Objects/Boilerplate/Debris.h"
#include "Objects/Boilerplate/Explosion.h"
#include "Objects/Boilerplate/FXFade.h"
#include "Objects/Boilerplate/ItemBox.h"
#include "Objects/Boilerplate/Ring.h"
#include "Objects/Boilerplate/ScoreBonus.h"
#include "Objects/Boilerplate/Zone.h"
#include "Boilerplate/Music.h"

#include "Objects/Boilerplate/CPZ/CPZSetup.h"
#include "Objects/Boilerplate/OOZ/OOZSetup.h"
#include "Objects/Boilerplate/HCZ/HCZSetup.h"
#include "Objects/Boilerplate/MMZ/FarPlane.h"

// game classes with notable modifications
#include "Objects/Player.h"
#include "Objects/ImageTrail.h"
#include "Objects/SpecialRing.h"

// new classes
#include "Objects/SuperFlicky.h"
#include "Objects/HyperStars.h"
#include "Objects/HPZ/HPZSetup.h"
#include "Objects/HPZ/HPZIntro.h"
#include "Objects/HPZ/HPZBeam.h"
#include "Objects/HPZ/HPZEmerald.h"

// enemy checking file
#include "Objects/Enemy.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void (*Music_SetMusicTrack)(const char*, uint8, uint32); // TODO move this to Music.h/c
int16 SuperFlickySlot;

void LoadHyperMusic(void) {
	Mod.Super(Music->classID, SUPER_STAGELOAD, NULL);
	Music_SetMusicTrack("Hyper.ogg", 10, 423801);
}

void StageSetup(void* data) {
	UNUSED(data);
	// extension variables -------------------------------------------------
	ExtMemory_size = 0;
	for (int32 i = 0; i != MAX_EXTMEM_ENTITIES; ++i) {
		ExtMemory[i] = (extmem_t){ EXTMEM_FREE_ID, 0, NULL };
	}

	// spare entity slots --------------------------------------------------
	SuperFlickySlot = 0;
	for (int16 i = ENTITY_COUNT - 1; i >= 0; --i) {
		Entity* entity = RSDK_GET_ENTITY_GEN(i);
		if (!entity->classID) {
			if (!SuperFlickySlot) SuperFlickySlot = i;
		}
		if (SuperFlickySlot) break;
	}

	// HPZ emerald sorting -------------------------------------------------
	if (HPZEmerald) {
		int32 size = 0;
		memset(SortedSuperEmeralds, 0, sizeof(Entity*) * 7);
		foreach_all(HPZEmerald, emerald) {
			if (emerald->type == HPZEMERALD_MASTER) continue;
			for (int32 i = 0; i != 7; ++i) {
				if (SortedSuperEmeralds[i] == NULL || SortedSuperEmeralds[i]->position.x > emerald->position.x) {
					if (SortedSuperEmeralds[i] != NULL) {
						memcpy(SortedSuperEmeralds + i + 1, SortedSuperEmeralds + i , (size - i) * sizeof(Entity*));
					}
					SortedSuperEmeralds[i] = (Entity*)emerald;
					++size;
					break;
				}
			}
			if (size == 7) break;
		}
	}
}

void StageCleanup(void* data) {
	UNUSED(data);

	EnemyInfoSlot = 0;
	memset(EnemyDefs, 0, sizeof(EnemyInfo) * 16);

	for (int32 i = 0; i != MAX_EXTMEM_ENTITIES; ++i) {
		if (ExtMemory[i].mem) free(ExtMemory[i].mem);
	}
}

void InitModAPI(void) {
	printf("******************** HYPERMANIA loaded ********************\n");
	Music_SetMusicTrack = Mod.GetPublicFunction(NULL, "Music_SetMusicTrack");
	Mod.AddModCallback(MODCB_ONSTAGELOAD, StageSetup);
	Mod.AddModCallback(MODCB_ONSTAGEUNLOAD, StageCleanup);

	// Boilerplate ------------------------------------------------------------
	Camera_State_FollowY = Mod.GetPublicFunction(NULL, "Camera_State_FollowY");
	Camera_ShakeScreen = Mod.GetPublicFunction(NULL, "Camera_ShakeScreen");
	Debris_State_Move = Mod.GetPublicFunction(NULL, "Debris_State_Move");
	Debris_State_FallAndFlicker = Mod.GetPublicFunction(NULL, "Debris_State_FallAndFlicker");
	FXFade_State_FadeIn = Mod.GetPublicFunction(NULL, "FXFade_State_FadeIn");
	ItemBox_State_Broken = Mod.GetPublicFunction(NULL, "ItemBox_State_Broken");
	ItemBox_Break = Mod.GetPublicFunction(NULL, "ItemBox_Break");
	Ring_State_Lost = Mod.GetPublicFunction(NULL, "Ring_State_Lost");
	Ring_Draw_Normal = Mod.GetPublicFunction(NULL, "Ring_Draw_Normal");
	Zone_GetZoneID = Mod.GetPublicFunction(NULL, "Zone_GetZoneID");
	Zone_StartFadeIn = Mod.GetPublicFunction(NULL, "Zone_StartFadeIn");
	Zone_StartFadeOut = Mod.GetPublicFunction(NULL, "Zone_StartFadeOut");
	MOD_REGISTER_OBJ_OVERLOAD(Music, NULL, NULL, NULL, NULL, NULL, LoadHyperMusic, NULL, NULL, NULL);
	MOD_REGISTER_OBJECT_HOOK(Animals);
	MOD_REGISTER_OBJECT_HOOK(Camera);
	MOD_REGISTER_OBJECT_HOOK(CollapsingPlatform);
	MOD_REGISTER_OBJECT_HOOK(Debris);
	MOD_REGISTER_OBJECT_HOOK(Explosion);
	MOD_REGISTER_OBJECT_HOOK(FXFade);
	MOD_REGISTER_OBJECT_HOOK(ItemBox);
	MOD_REGISTER_OBJECT_HOOK(Ring);
	MOD_REGISTER_OBJECT_HOOK(ScoreBonus);
	MOD_REGISTER_OBJECT_HOOK(Zone);
	HOOK_ENEMY_OBJECTS;
	IMPORT_ENEMY_FUNCTIONS;

	// zone specific stuff
	MOD_REGISTER_OBJECT_HOOK(FarPlane);
	MOD_REGISTER_OBJECT_HOOK(CPZSetup);
	MOD_REGISTER_OBJECT_HOOK(HCZSetup);
	MOD_REGISTER_OBJECT_HOOK(OOZSetup);

	// Mod ------------------------------------------------------------
	Player_GiveScore = Mod.GetPublicFunction(NULL, "Player_GiveScore");
	Player_CheckBadnikBreak = Mod.GetPublicFunction(NULL, "Player_CheckBadnikBreak");
	Player_GetHitbox = Mod.GetPublicFunction(NULL, "Player_GetHitbox");
	Player_State_Air = Mod.GetPublicFunction(NULL, "Player_State_Air");
	Player_State_KnuxWallClimb = Mod.GetPublicFunction(NULL, "Player_State_KnuxWallClimb");
	Player_State_KnuxGlideLeft = Mod.GetPublicFunction(NULL, "Player_State_KnuxGlideLeft");
	Player_State_KnuxGlideRight = Mod.GetPublicFunction(NULL, "Player_State_KnuxGlideRight");
	Player_CheckCollisionTouch = Mod.GetPublicFunction(NULL, "Player_CheckCollisionTouch");

	Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_JumpAbility_Sonic"), Player_JumpAbility_Sonic_Hook, true);
	Mod.RegisterStateHook(Player_State_KnuxGlideLeft, Player_State_KnuxGlide_Hook, true);
	Mod.RegisterStateHook(Player_State_KnuxGlideRight, Player_State_KnuxGlide_Hook, true);

	SpecialRing_State_Flash = Mod.GetPublicFunction(NULL, "SpecialRing_State_Flash");
	Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "SpecialRing_State_Warp"), SpecialRing_State_Warp_Hook, false);

	MOD_REGISTER_OBJ_OVERLOAD(Player, Player_Update_Hook, NULL, NULL, Player_Draw_Hook, NULL, Player_StageLoad_Hook, NULL, NULL, NULL);
	MOD_REGISTER_OBJ_OVERLOAD(ImageTrail, NULL, NULL, NULL, ImageTrail_Draw_Hook, NULL, NULL, NULL, NULL, NULL);
	MOD_REGISTER_OBJ_OVERLOAD(SpecialRing, NULL, NULL, NULL, SpecialRing_Draw_Hook, NULL, NULL, NULL, NULL, NULL);
	MOD_REGISTER_OBJ_OVERLOAD(HPZEmerald, HPZEmerald_Update_Hook, NULL, NULL, HPZEmerald_Draw_Hook, HPZEmerald_Create_Hook, HPZEmerald_StageLoad_Hook, NULL, NULL, NULL);

	// New --------------------------------------------------------------------
	RSDK_REGISTER_OBJECT(SuperFlicky);
	RSDK_REGISTER_OBJECT(HyperStars);
	RSDK_REGISTER_OBJECT(HPZSetup);
	RSDK_REGISTER_OBJECT(HPZIntro);
	RSDK_REGISTER_OBJECT(HPZBeam);
}

#if RETRO_USE_MOD_LOADER
#  define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id) {
#  if MANIA_USE_PLUS
	LinkGameLogicDLL(info);
#  else
	LinkGameLogicDLL(*info);
#  endif
	globals = Mod.GetGlobals();
	modID = id;
	InitModAPI();
	return true;
}
#endif
