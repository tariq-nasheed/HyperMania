#include "util.h"

HM_global_t HM_global;
bool32 HPZ_SuperSpecialStage;

// =============================================================================

// -----------------------------------------------------------------------------

// =============================================================================
// max output length: 47 characters (counting null terminator) (rounded to 64 to avoid stack corruptions)
#define SAVEMSG_LEN 64
static void HM_Save_FormatString(char* str) {
	char emerald_mask[8];
	for (int32 i = 0; i != 8; ++i) {
		emerald_mask[i] = (HM_global.currentSave->superEmeralds & 1 << i) ? '1' : '0';
	}
	sprintf(
		str,
		"emeralds %stransfered, current mask: %.8s",
		(HM_global.currentSave->transferedEmeralds) ? "" : "not ",
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
		HYPERMANIA_PRINT(PRINT_ERROR, "failed to save persistent data");
		return;
	}
	HYPERMANIA_PRINT(PRINT_NORMAL, "persistent data saved");

	if (!HM_global.currentSave) return;
	char save_message[SAVEMSG_LEN];
	HM_Save_FormatString(save_message);
	HYPERMANIA_PRINT(PRINT_NORMAL, "save info: %s", save_message);
}

static void HM_Save_LoadCB(int32 status) {
#if MANIA_USE_PLUS
	const bool32 success = (status == STATUS_OK || status == STATUS_NOTFOUND) ? true : false;
#else
	const bool32 success = (status) ? true : false;
#endif
	if (!success) {
		HYPERMANIA_PRINT(PRINT_ERROR, "failed to load persistent data");
		return;
	}
	HYPERMANIA_PRINT(PRINT_NORMAL, "persistent data loaded");

	char save_message[SAVEMSG_LEN];
	HM_Save_FormatString(save_message);
	HYPERMANIA_PRINT(PRINT_NORMAL, "save info: %s", save_message);
}


HM_SaveRAM* HM_Save_GetDataPtr(int32 slot, bool32 encore) {
	if (encore) return &HM_global.saveRAM[slot % 3 + 8];
	else        return &HM_global.saveRAM[slot % 8];
	return &HM_global.noSaveSlot;
}

void HM_Save_SaveFile() {
	SaveRAM* save = GetSaveRAM_Safe();
	if (save && save->chaosEmeralds == 0b00000000) {
		HYPERMANIA_PRINT(PRINT_NORMAL, "erased save game detected! deleting super emerald data");
		HM_global.currentSave->transferedEmeralds = 0b00000000;
		HM_global.currentSave->superEmeralds      = 0b00000000;
	}
#if RETRO_REV02
	API.SaveUserFile(SAVE_FILE_NAME, &HM_global.saveRAM, sizeof(HM_global.saveRAM), HM_Save_SaveCB, false);
#else
	RSDK.SaveUserFile(SAVE_FILE_NAME, &HM_global.saveRAM, sizeof(HM_global.saveRAM));
#endif
}

void HM_Save_LoadFile() {
#if RETRO_REV02
	API.LoadUserFile(SAVE_FILE_NAME, &HM_global.saveRAM, sizeof(HM_global.saveRAM), HM_Save_LoadCB);
#else
	RSDK.LoadUserFile(SAVE_FILE_NAME, &HM_global.saveRAM, sizeof(HM_global.saveRAM));
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
		HYPERMANIA_PRINT(PRINT_ERROR, "max extended memory objects already reached");
		return NULL;
	}
	if (owner_id >= ENTITY_COUNT - TEMPENTITY_COUNT) {
		HYPERMANIA_PRINT(PRINT_ERROR, "temporary entitities are invalid");
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
