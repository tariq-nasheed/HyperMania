#include "ModFunctions.h"

HM_global_t HM_global;
bool32 HPZ_SuperSpecialStage;

// =============================================================================

// -----------------------------------------------------------------------------

// =============================================================================
#define SAVEMSG_LEN 64
#define SAVE_FILE_NAME "HyperManiaSaveData.bin"

static void HM_Save_FormatString(char* str) {
	char emerald_mask[8];
	for (int32 i = 0; i != 8; ++i) {
		emerald_mask[i] = (HM_globals->currentSave->superEmeralds & 1 << i) ? '1' : '0';
	}
	sprintf(
		str,
		"emeralds %stransfered, current mask: %.8s",
		(HM_globals->currentSave->transferedEmeralds) ? "" : "not ",
		emerald_mask
	);
}

static void HM_Save_SaveCB(int32 status) {
#if MANIA_USE_PLUS
	const bool32 success = (status == STATUS_OK || status == STATUS_NOTFOUND) ? true : false;
#else
	const bool32 success = (status) ? true : false;
#endif
	if (!success) {
		MOD_PRINT(PRINT_ERROR, "failed to save persistent data", "");
		return;
	}
	MOD_PRINT(PRINT_NORMAL, "persistent data saved", "");

	if (!HM_globals->currentSave) return;
	char save_message[SAVEMSG_LEN];
	HM_Save_FormatString(save_message);
	MOD_PRINT(PRINT_NORMAL, "save info: %s", save_message);
}

static void HM_Save_LoadCB(int32 status) {
#if MANIA_USE_PLUS
	const bool32 success = (status == STATUS_OK || status == STATUS_NOTFOUND) ? true : false;
#else
	const bool32 success = (status) ? true : false;
#endif
	if (!success) {
		MOD_PRINT(PRINT_ERROR, "failed to load persistent data", "");
		return;
	}
	MOD_PRINT(PRINT_NORMAL, "persistent data loaded", "");

	char save_message[SAVEMSG_LEN];
	HM_Save_FormatString(save_message);
	MOD_PRINT(PRINT_NORMAL, "save info: %s", save_message);
}


HM_SaveRAM* HM_Save_GetDataPtr(int32 slot, bool32 encore) {
	if (encore) return &HM_globals->saveRAM[slot % 3 + 8];
	else        return &HM_globals->saveRAM[slot % 8];
	return &HM_globals->noSaveSlot;
}

void HM_Save_SaveFile() {
	SaveRAM* save = GetSaveRAM_Safe();
	if (save && save->chaosEmeralds == 0b00000000) {
		MOD_PRINT(PRINT_NORMAL, "erased save game detected! deleting super emerald data", "");
		HM_globals->currentSave->transferedEmeralds = 0b00000000;
		HM_globals->currentSave->superEmeralds      = 0b00000000;
	}
#if RETRO_REV02
	API.SaveUserFile(SAVE_FILE_NAME, &HM_globals->saveRAM, sizeof(HM_globals->saveRAM), HM_Save_SaveCB, false);
#else
	RSDK.SaveUserFile(SAVE_FILE_NAME, &HM_globals->saveRAM, sizeof(HM_globals->saveRAM));
#endif
}

void HM_Save_LoadFile() {
#if RETRO_REV02
	API.LoadUserFile(SAVE_FILE_NAME, &HM_globals->saveRAM, sizeof(HM_globals->saveRAM), HM_Save_LoadCB);
#else
	RSDK.LoadUserFile(SAVE_FILE_NAME, &HM_globals->saveRAM, sizeof(HM_globals->saveRAM));
#endif
}


// =============================================================================

// -----------------------------------------------------------------------------

// =============================================================================
extmem_t     ExtMemory[MAX_EXTMEM_ENTITIES];
uint32       ExtMemory_size;
int8 ExtMemoryIndex[ENTITY_COUNT - TEMPENTITY_COUNT];
int8 ExtMemoryRevIndex[MAX_EXTMEM_ENTITIES];

void* AllocExtMem(int32 owner_id, uint32 bytes) {
	if (ExtMemory_size == MAX_EXTMEM_ENTITIES) {
		MOD_PRINT(PRINT_ERROR, "max extended memory objects already reached", "");
		return NULL;
	}
	if (owner_id >= ENTITY_COUNT - TEMPENTITY_COUNT) {
		MOD_PRINT(PRINT_ERROR, "temporary entitities are invalid", "");
		return NULL;
	}

	int32 id = 0;
	if (ExtMemoryIndex[owner_id] == EXTMEM_FREE_ID) {
		while (ExtMemoryRevIndex[id] != EXTMEM_FREE_ID) ++id;
		ExtMemoryRevIndex[id] = owner_id;
		ExtMemoryIndex[owner_id] = id;
		++ExtMemory_size;
	} else {
		id = ExtMemoryIndex[owner_id];
	}

	if (!ExtMemory[id].mem) {
		ExtMemory[id].mem = malloc(bytes);
	} else if (bytes != ExtMemory[id].size) {
		ExtMemory[id].mem = realloc(ExtMemory[id].mem, bytes);
	}
	ExtMemory[id].size = bytes;
	return ExtMemory[id].mem;
}

void* GetExtMem(int32 owner_id) {
	const int32 index = ExtMemoryIndex[owner_id];
	return (index == EXTMEM_FREE_ID) ? NULL : ExtMemory[index].mem;
}

void FreeExtMem(int32 owner_id) {
	ExtMemoryRevIndex[ExtMemoryIndex[owner_id]] = EXTMEM_FREE_ID;
	ExtMemoryIndex[owner_id] = EXTMEM_FREE_ID;
	--ExtMemory_size;
}


// =============================================================================

// -----------------------------------------------------------------------------

// =============================================================================
void (*APICallback_TrackEnemyDefeat)(uint8 zoneID, uint8 actID, uint8 playerID, int32 x, int32 y);
void (*TimeAttackData_TrackEnemyDefeat)(StatInfo* stat, uint8 zoneID, uint8 actID, uint8 characterID, bool32 encore, int32 x, int32 y);

bool32 AddATKClass(uint16 id, attackinfo_t info) {
	if (HM_globals->AttackableClasses_startidx == ENTATTACK_INVALID) HM_globals->AttackableClasses_startidx = id;
	const uint32 index = id - HM_globals->AttackableClasses_startidx;
	if (index >= MAX_ATTACKABLE_CLASSES) {
		MOD_PRINT(PRINT_ERROR, "Attackable class %d has a index (%d) that exceeds max difference from epoch", id, index);
	} else {
		memcpy(&HM_globals->AttackableClasses[index], &info, sizeof(attackinfo_t));
		++HM_globals->AttackableClasses_size;
	}
}

attackinfo_t* GetATKClassInfo(uint16 id) {
	const int32 index = id - HM_globals->AttackableClasses_startidx;
	if (HM_globals->AttackableClasses_startidx > id  || index >= MAX_ATTACKABLE_CLASSES) return NULL;
	return &HM_globals->AttackableClasses[index];
}

attackinfo_t* IsATKEntity(Entity* entity, uint8 blacklist_mask, bool32 checkVisible) {
	if (!entity) return NULL;
	attackinfo_t* info = GetATKClassInfo(entity->classID);
	if (!info) return NULL;

	const uint32 index = entity->classID - HM_globals->AttackableClasses_startidx;
	if (index >= MAX_ATTACKABLE_CLASSES || !HM_globals->AttackableClasses[index].checkVulnerable) return false;
	if (info->checkVulnerable(entity) && !(info->flags & blacklist_mask)) { // mask check happens near the end to account for hotaru hi-watts BULLSHIT
		if (!checkVisible) return info;

		const Vector2 old_pos = entity->position;
		if (info->adjustPos) info->adjustPos(entity);
		Vector2 checkPos = entity->position;
		if (FarPlane && entity->drawGroup < 3) {
			entity->position.x = FarPlane->worldPos.x + ((entity->position.x - FarPlane->originPos.x) >> 1);
			entity->position.y = FarPlane->worldPos.y + ((entity->position.y - FarPlane->originPos.y) >> 1);
		}
		if (RSDK.CheckPosOnScreen(&checkPos, &entity->updateRange)) {
			entity->position = old_pos;
			return info;
		}
		entity->position = old_pos;
	}
	return NULL;
}


bool32 Generic_CheckVulnerable(Entity* self) { return true; }
Hitbox* Generic_GetHitbox(Entity* self) { return NULL; }

void Generic_OnHit(EntityPlayer* player, Entity* self) {
	const uint32 index = self->classID - HM_globals->AttackableClasses_startidx;
	uint8 flags = HM_globals->AttackableClasses[index].flags;
	Generic_BadnikBreak(player, self, (flags & ATKFLAG_NOANIMAL) ? false : true);
}

void Generic_BadnikBreak(EntityPlayer* player, Entity* badnik, bool32 spawnAnimals) {
	if (spawnAnimals) CREATE_ENTITY(Animals, INT_TO_VOID((Animals->animalTypes[(RSDK.Rand(0, 32) >> 4)]) + 1), badnik->position.x, badnik->position.y);
	EntityExplosion* explosion = CREATE_ENTITY(Explosion, INT_TO_VOID(EXPLOSION_ENEMY), badnik->position.x, badnik->position.y);
	explosion->drawGroup       = Zone->objectDrawGroup[1];
	RSDK.PlaySfx(Explosion->sfxDestroy, false, 255);

	if (Zone_GetZoneID() > ZONE_INVALID) {
		int32 characterID = 0;
		switch (player->characterID) {
			case ID_SONIC: characterID = 1; break;
			case ID_TAILS: characterID = 2; break;
			case ID_KNUCKLES: characterID = 3; break;
#if MANIA_USE_PLUS
			case ID_MIGHTY: characterID = 4; break;
			case ID_RAY: characterID = 5; break;
#endif
			default: characterID = 0; break;
		}

#if MANIA_USE_PLUS
		StatInfo info;
		TimeAttackData_TrackEnemyDefeat(&info, Zone_GetZoneID(), Zone->actID, characterID, SceneInfo->filter == (FILTER_BOTH | FILTER_ENCORE),
		                                FROM_FIXED(badnik->position.x), FROM_FIXED(badnik->position.y));
		API.TryTrackStat(&info);
#else
		APICallback_TrackEnemyDefeat(Zone_GetZoneID(), Zone->actID, characterID, FROM_FIXED(badnik->position.x), FROM_FIXED(badnik->position.y));
#endif
	}

	if (globals->gameMode != MODE_COMPETITION) player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
	EntityScoreBonus* scoreBonus = CREATE_ENTITY(ScoreBonus, NULL, badnik->position.x, badnik->position.y);
	scoreBonus->drawGroup        = Zone->objectDrawGroup[1];
	scoreBonus->animator.frameID = player->scoreBonus;

	switch (player->scoreBonus) {
		case 0: Player_GiveScore(player, 100); break;
		case 1: Player_GiveScore(player, 200); break;
		case 2: Player_GiveScore(player, 500); break;
		case 14: Player_GiveScore(player, 1000); break;
		case 15: Player_GiveScore(player, 10000); break;
		default: break;
	}
	if (player->scoreBonus < 15) player->scoreBonus++;

	destroyEntity(badnik);
	badnik->active = ACTIVE_DISABLED;
}

// hotaru and rexon lol
void Generic_BadnikBreak_NoEntity(EntityPlayer* player, Vector2 position, bool32 spawnAnimals) {
	if (spawnAnimals) CREATE_ENTITY(Animals, INT_TO_VOID((Animals->animalTypes[(RSDK.Rand(0, 32) >> 4)]) + 1), position.x, position.y);
	EntityExplosion *explosion = CREATE_ENTITY(Explosion, INT_TO_VOID(EXPLOSION_ENEMY), position.x, position.y);
	explosion->drawGroup       = Zone->objectDrawGroup[1];
	RSDK.PlaySfx(Explosion->sfxDestroy, false, 255);

	if (Zone_GetZoneID() > ZONE_INVALID) {
		int32 characterID = 0;
		switch (player->characterID) {
			case ID_SONIC: characterID = 1; break;
			case ID_TAILS: characterID = 2; break;
			case ID_KNUCKLES: characterID = 3; break;
#if MANIA_USE_PLUS
			case ID_MIGHTY: characterID = 4; break;
			case ID_RAY: characterID = 5; break;
#endif
			default: characterID = 0; break;
		}

#if MANIA_USE_PLUS
		StatInfo info;
		TimeAttackData_TrackEnemyDefeat(&info, Zone_GetZoneID(), Zone->actID, characterID, SceneInfo->filter == (FILTER_BOTH | FILTER_ENCORE),
		                                FROM_FIXED(position.x), FROM_FIXED(position.y));
		API.TryTrackStat(&info);
#else
		APICallback_TrackEnemyDefeat(Zone_GetZoneID(), Zone->actID, characterID, FROM_FIXED(position.x), FROM_FIXED(position.y));
#endif
	}

	if (globals->gameMode != MODE_COMPETITION) player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
	EntityScoreBonus* scoreBonus = CREATE_ENTITY(ScoreBonus, NULL, position.x, position.y);
	scoreBonus->drawGroup        = Zone->objectDrawGroup[1];
	scoreBonus->animator.frameID = player->scoreBonus;

	switch (player->scoreBonus) {
		case 0: Player_GiveScore(player, 100); break;
		case 1: Player_GiveScore(player, 200); break;
		case 2: Player_GiveScore(player, 500); break;
		case 14: Player_GiveScore(player, 1000); break;
		case 15: Player_GiveScore(player, 10000); break;
		default: break;
	}
	if (player->scoreBonus < 15) player->scoreBonus++;
}


// =============================================================================

// -----------------------------------------------------------------------------

// =============================================================================
clientarray_t clients;

bool32 HMAPI_InitClient(const char* _modID, uint16* clearFrames) {
	clients.mem = realloc(clients.mem, sizeof(clientinfo_t) * (clients.len + 1));
	clientinfo_t* back = &clients.mem[clients.len];
	++clients.len;
}

HM_global_t* HMAPI_GetGlobals() { return HM_globals; }

bool32 HMAPI_AddCharacter(const char* _modID, uint16 characterID, hyperpal_t* paletteInfo) {
	clientinfo_t* client = NULL;
	for (int32 i = 0; i != clients.len; ++i) {
		if (strcmp(_modID, clients.mem[i].modID) == 0) {
			client = &clients.mem[i];
			break;
		}
	}
	if (!client) {
		MOD_PRINT(PRINT_ERROR, "could not find client named \'%s\'", _modID);
		return false;
	}

	client->players.mem = realloc(client->players.mem, sizeof(playerinfo_t) * (client->players.count + 1));
	playerinfo_t* back = &client->players.mem[client->players.count];
	++client->players.count;
	back->id = characterID;
	back->paletteInfo = paletteInfo;
}

void HMAPI_ScreenFlash(EntityPlayer* player, float intensity) {
	if (HM_globals->config.screenFlashFactor <= 0.0) return;

	EntityFXFade* fade = CREATE_ENTITY(FXFade, INT_TO_VOID(0xF0F0F0), player->position.x, player->position.y);
	if (HM_globals->config.screenFlashFactor < (1.0 / intensity)) {
		fade->timer = 0x200 * intensity * HM_globals->config.screenFlashFactor;
		fade->state = FXFade_State_FadeIn;
	} else {
		fade->speedIn = 0x200 * intensity * HM_globals->config.screenFlashFactor;
		fade->state = FXFade_State_FadeOut;
	}
	fade->speedOut = 0x30 * HM_globals->config.screenFlashFactor;
}

void HMAPI_BadnikScreenClear(EntityPlayer* player) {
	for (int16 i = 0; i != ENTITY_COUNT; ++i) {
		Entity* entity = RSDK_GET_ENTITY_GEN(i);
		const attackinfo_t* info = IsATKEntity(entity, ATKFLAG_ISBOSS, true);
		if (!info) continue;

		const Vector2 old_pos = entity->position;
		if (info->adjustPos) info->adjustPos(entity);
		info->onHit(player, entity);
		entity->position = old_pos;
	}
}

void HMAPI_ItemBoxScreenClear(EntityPlayer* player, bool32 force) {
	if (!HM_globals->config.GSWitemBoxes && !force) return;
	foreach_all(ItemBox, box) {
		if (RSDK.CheckOnScreen(box, NULL) && (void*)box->state != (void*)ItemBox_State_Broken) {
			ItemBox_Break(box, player);
		}
	}
}

#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void AddAPIFunctions() {
	ADD_PUBLIC_FUNC(HMAPI_InitClient);
	ADD_PUBLIC_FUNC(HMAPI_GetGlobals);
	ADD_PUBLIC_FUNC(HMAPI_ScreenFlash);
	ADD_PUBLIC_FUNC(HMAPI_AddCharacter);
	ADD_PUBLIC_FUNC(HMAPI_BadnikScreenClear);
	ADD_PUBLIC_FUNC(HMAPI_ItemBoxScreenClear);
	ADD_PUBLIC_FUNC(AddATKClass);
	ADD_PUBLIC_FUNC(GetATKClassInfo);
	ADD_PUBLIC_FUNC(IsATKEntity);
	ADD_PUBLIC_FUNC(HM_Save_SaveFile);
	ADD_PUBLIC_FUNC(HM_Save_LoadFile);
}