#include "../GameAPI/C/GameAPI/Game.h"

#include "util.h"
#include "ModConfig.h"

// game classes litte/no notable modifications
#include "Objects/Boilerplate/SaveGame.h"
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
#include "Boilerplate/Global/PauseMenu.h"

#include "Objects/Boilerplate/CPZ/CPZSetup.h"
#include "Objects/Boilerplate/OOZ/OOZSetup.h"
#include "Objects/Boilerplate/HCZ/HCZSetup.h"
#include "Objects/Boilerplate/MMZ/FarPlane.h"
#include "Objects/Boilerplate/ERZ/ERZStart.h"
#include "Objects/Boilerplate/BSS/BSS_Setup.h"

// game classes with notable modifications
#include "Objects/Player.h"
#include "Objects/ImageTrail.h"
#include "Objects/SpecialRing.h"
#include "Objects/UFO_Setup.h"
#include "Objects/UFO_Player.h"
#include "Objects/SpecialClear.h"
#include "Objects/HUD.h"
#include "Objects/UISaveSlot.h"
#include "Objects/HPZ/HPZEmerald.h"

// new classes
#include "Objects/SuperFlicky.h"
#include "Objects/HyperStars.h"
#include "Objects/HPZ/HPZSetup.h"
#include "Objects/HPZ/HPZIntro.h"
#include "Objects/HPZ/HPZBeam.h"

// enemy checking file
#include "Objects/Enemy.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

int16 SuperFlickySlot;
ModConfig_t ModConfig;

bool32 loaded_already = false;
void StageSetup(void* data) {
	UNUSED(data);

	// loading save file ---------------------------------------------------
	if (globals->saveSlotID == NO_SAVE_SLOT) {
		HM_global.currentSave = &HM_global.noSaveSlot;
	} else {
		HM_global.currentSave =  HM_Save_GetDataPtr(globals->saveSlotID, globals->gameMode == MODE_ENCORE);
	}
	// mnmggggggggggggmmmmmmmm
	if (!loaded_already) {
		HM_Save_LoadFile();
		loaded_already = true;
	}

	// extension variables -------------------------------------------------
	ExtMemory_size = 0;
	for (int32 i = 0; i != MAX_EXTMEM_ENTITIES; ++i) {
		ExtMemory[i] = (extmem_t){ EXTMEM_FREE_ID, 0 };
	}
	memset(ExtMemoryIndex, EXTMEM_FREE_ID, sizeof(ExtMemoryIndex));
	memset(ExtMemoryRevIndex, EXTMEM_FREE_ID, sizeof(ExtMemoryRevIndex));

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

	if (!UFO_Setup) HPZ_SuperSpecialStage = false;
	if (HPZSetup) {
		HPZ_SuperSpecialStage = true;
	}

	// saving save file ----------------------------------------------------
	if (globals->saveSlotID != NO_SAVE_SLOT && HM_global.currentSave && HM_global.currentSave != &HM_global.noSaveSlot) HM_Save_SaveFile();

	// enemy callback shit idk ---------------------------------------------
	EnemyInfoSlot = 0;
	memset(EnemyDefs, 0, sizeof(EnemyInfo) * 16);

	// ext vars ------------------------------------------------------------
	for (int32 i = 0; i != MAX_EXTMEM_ENTITIES; ++i) {
		if (ExtMemory[i].mem) free(ExtMemory[i].mem);
	}
}

void InitModAPI(void) {
	printf("******************** HYPERMANIA loaded ********************\n");
	Mod.AddModCallback(MODCB_ONSTAGELOAD, StageSetup);
	Mod.AddModCallback(MODCB_ONSTAGEUNLOAD, StageCleanup);

	// Config --------------------------------------------------------------
	ModConfig.originsHyperDash = Mod.GetSettingsBool("", "Config:originsHyperDash", false);
	ModConfig.hyperStyle = Mod.GetSettingsInteger("", "Config:hyperStyle", 0);
	Mod.SetSettingsBool("Config:originsHyperDash", ModConfig.originsHyperDash);
	Mod.SetSettingsInteger("Config:hyperStyle", ModConfig.hyperStyle);
	Mod.SaveSettings();

	// Boilerplate ---------------------------------------------------------
	OBJ_MUSIC_SETUP;
	OBJ_RING_SETUP;
	OBJ_UFO_SETUP_SETUP;
	OBJ_PAUSEMENU_SETUP;
	Camera_State_FollowY = Mod.GetPublicFunction(NULL, "Camera_State_FollowY");
	Camera_ShakeScreen = Mod.GetPublicFunction(NULL, "Camera_ShakeScreen");
	Debris_State_Move = Mod.GetPublicFunction(NULL, "Debris_State_Move");
	Debris_State_FallAndFlicker = Mod.GetPublicFunction(NULL, "Debris_State_FallAndFlicker");
	FXFade_State_FadeIn = Mod.GetPublicFunction(NULL, "FXFade_State_FadeIn");
	FXFade_State_FadeOut = Mod.GetPublicFunction(NULL, "FXFade_State_FadeOut");
	ItemBox_State_Broken = Mod.GetPublicFunction(NULL, "ItemBox_State_Broken");
	ItemBox_Break = Mod.GetPublicFunction(NULL, "ItemBox_Break");
	Zone_GetZoneID = Mod.GetPublicFunction(NULL, "Zone_GetZoneID");
	Zone_StartFadeIn = Mod.GetPublicFunction(NULL, "Zone_StartFadeIn");
	Zone_StartFadeOut = Mod.GetPublicFunction(NULL, "Zone_StartFadeOut");
	MOD_REGISTER_OBJECT_HOOK(Animals);
	MOD_REGISTER_OBJECT_HOOK(Camera);
	MOD_REGISTER_OBJECT_HOOK(CollapsingPlatform);
	MOD_REGISTER_OBJECT_HOOK(Debris);
	MOD_REGISTER_OBJECT_HOOK(Explosion);
	MOD_REGISTER_OBJECT_HOOK(FXFade);
	MOD_REGISTER_OBJECT_HOOK(ItemBox);
	MOD_REGISTER_OBJECT_HOOK(ScoreBonus);
	MOD_REGISTER_OBJECT_HOOK(Zone);
	HOOK_ENEMY_OBJECTS;
	IMPORT_ENEMY_FUNCTIONS;

	// zone specific stuff
	MOD_REGISTER_OBJECT_HOOK(FarPlane);
	MOD_REGISTER_OBJECT_HOOK(CPZSetup);
	MOD_REGISTER_OBJECT_HOOK(HCZSetup);
	MOD_REGISTER_OBJECT_HOOK(OOZSetup);
	MOD_REGISTER_OBJECT_HOOK(ERZStart);
	MOD_REGISTER_OBJECT_HOOK(BSS_Setup);

	// Mod ------------------------------------------------------------
	OBJ_SAVE_SETUP;
	OBJ_PLAYER_SETUP;
	OBJ_SPECIALRING_SETUP;
	OBJ_UFO_PLAYER_SETUP;
	OBJ_SPECIALCLEAR_SETUP;
	OBJ_UISAVESLOT_SETUP;
	OBJ_HUD_SETUP;


	MOD_REGISTER_OBJ_OVERLOAD(ImageTrail, NULL, NULL, NULL, ImageTrail_Draw_Hook, NULL, NULL, NULL, NULL, NULL);
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
