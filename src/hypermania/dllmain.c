#include "All.c"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

int16 SuperFlickySlot;

bool32 loaded_already = false;
void StageSetup(void* data) {
	UNUSED(data);

	// loading save file ---------------------------------------------------
	if (globals->saveSlotID == NO_SAVE_SLOT) {
		HM_globals->currentSave = &HM_globals->noSaveSlot;
	} else {
#if MANIA_USE_PLUS
		HM_globals->currentSave =  HM_Save_GetDataPtr(globals->saveSlotID, globals->gameMode == MODE_ENCORE);
#else
		HM_globals->currentSave =  HM_Save_GetDataPtr(globals->saveSlotID, false);
#endif
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
	if (globals->saveSlotID != NO_SAVE_SLOT && HM_globals->currentSave && HM_globals->currentSave != &HM_globals->noSaveSlot) HM_Save_SaveFile();

	// Attackable Classes --------------------------------------------------
	HM_globals->AttackableClasses_size = 0;
	HM_globals->AttackableClasses_startidx = ENTATTACK_INVALID;
	memset(HM_globals->AttackableClasses, 0, sizeof(HM_globals->AttackableClasses));

	// ext vars ------------------------------------------------------------
	for (int32 i = 0; i != MAX_EXTMEM_ENTITIES; ++i) {
		if (ExtMemory[i].mem) free(ExtMemory[i].mem);
	}
}

void InitModAPI() {
	printf(
		"\x1b[93mH\x1b[91mY\x1b[95mP\x1b[96mE\x1b[32mR"
		"\x1b[92mM\x1b[37mA\x1b[93mN\x1b[91mI\x1b[95mA\x1b[0m"
	);
	printf(" loaded\n");

	AddAPIFunctions();
	HM_globals = calloc(1, sizeof(HM_global_t));

	Mod.AddModCallback(MODCB_ONSTAGELOAD, StageSetup);
	Mod.AddModCallback(MODCB_ONSTAGEUNLOAD, StageCleanup);

	// Config --------------------------------------------------------------
	HM_globals->config.hyperStyle = Mod.GetSettingsInteger("", "Config:hyperStyle", 0);
	HM_globals->config.hyperFlashDropDash = Mod.GetSettingsBool("", "Config:hyperFlashDropDash", true);
	HM_globals->config.hyperFlashForwarding = Mod.GetSettingsBool("", "Config:hyperFlashForwarding", false);
	HM_globals->config.screenFlashFactor = Mod.GetSettingsFloat("", "Config:screenFlashFactor", 1.0);
	HM_globals->config.twoHeavensMode = Mod.GetSettingsBool("", "Config:twoHeavensMode", false);
	HM_globals->config.enableHyperMusic = Mod.GetSettingsBool("", "Config:enableHyperMusic", true);
	HM_globals->config.GSWburst = Mod.GetSettingsBool("", "Config:GSWburst", true);
	HM_globals->config.GSWitemBoxes = Mod.GetSettingsBool("", "Config:GSWitemBoxes", true);
	HM_globals->config.JEAjank = Mod.GetSettingsBool("", "Config:JEAjank", false);
	HM_globals->config.superTailsOnly = Mod.GetSettingsBool("", "Config:superTailsOnly", false);
	Mod.SetSettingsInteger("Config:hyperStyle", HM_globals->config.hyperStyle);
	Mod.SetSettingsBool("Config:hyperFlashDropDash", HM_globals->config.hyperFlashDropDash);
	Mod.SetSettingsBool("Config:hyperFlashForwarding", HM_globals->config.hyperFlashForwarding);
	Mod.SetSettingsFloat("Config:screenFlashFactor", HM_globals->config.screenFlashFactor);
	Mod.SetSettingsBool("Config:twoHeavensMode", HM_globals->config.twoHeavensMode);
	Mod.SetSettingsBool("Config:enableHyperMusic", HM_globals->config.enableHyperMusic);
	Mod.SetSettingsBool("Config:GSWburst", HM_globals->config.GSWburst);
	Mod.SetSettingsBool("Config:GSWitemBoxes", HM_globals->config.GSWitemBoxes);
	Mod.SetSettingsBool("Config:JEAjank", HM_globals->config.JEAjank);
	Mod.SetSettingsBool("Config:superTailsOnly", HM_globals->config.superTailsOnly);
	Mod.SaveSettings();

	// Boilerplate ---------------------------------------------------------
	OBJ_MUSIC_SETUP;
	OBJ_RING_SETUP;
	OBJ_UFO_SETUP_SETUP;
	OBJ_PAUSEMENU_SETUP;
	OBJ_FARPLANE_SETUP;
	Camera_State_FollowXY = Mod.GetPublicFunction(NULL, "Camera_State_FollowXY");
	Camera_State_FollowY = Mod.GetPublicFunction(NULL, "Camera_State_FollowY");
	Camera_ShakeScreen = Mod.GetPublicFunction(NULL, "Camera_ShakeScreen");
	IMPORT_PUBLIC_FUNC(Camera_SetupLerp);
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
	MOD_REGISTER_OBJECT_HOOK(InvincibleStars);

	// zone specific stuff
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
	OBJ_LEVELSELECT_SETUP;
	OBJ_HUD_SETUP;
	OBJ_PLANESEESAW_SETUP;
	OBJ_DEBRIS_SETUP;
	MOD_REGISTER_OBJ_OVERLOAD(ImageTrail, NULL, ImageTrail_LateUpdate_OVERLOAD, NULL, ImageTrail_Draw_OVERLOAD, ImageTrail_Create_OVERLOAD, NULL, NULL, NULL, NULL);
	MOD_REGISTER_OBJ_OVERLOAD(HPZEmerald, HPZEmerald_Update_Hook, NULL, NULL, HPZEmerald_Draw_Hook, HPZEmerald_Create_Hook, HPZEmerald_StageLoad_Hook, NULL, NULL, NULL);

	// New --------------------------------------------------------------------
	RSDK_REGISTER_OBJECT(SuperFlicky);
	RSDK_REGISTER_OBJECT(HyperStars);
	RSDK_REGISTER_OBJECT(JetGlideEffect);
	RSDK_REGISTER_OBJECT(HPZSetup);
	RSDK_REGISTER_OBJECT(HPZIntro);
	RSDK_REGISTER_OBJECT(HPZBeam);
}

#if RETRO_USE_MOD_LOADER
void InitModAPI();

bool32 LinkModLogic(EngineInfo *info, const char *id) {
  #if MANIA_USE_PLUS
	LinkGameLogicDLL(info);
  #else
	LinkGameLogicDLL(*info);
  #endif
	globals = Mod.GetGlobals();
	modID = id;
	InitModAPI();
	return true;
}
#endif
