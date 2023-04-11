#include "util.h"

HM_global_t HM_global;
bool32 HPZ_SuperSpecialStage;

// =============================================================================

// -----------------------------------------------------------------------------

// =============================================================================
// max output length: 47 characters (counting null terminator)
#define SAVEMSG_LEN 47
static void HM_Save_FormatString(char* str) {
	char emerald_mask[7];
	for (int32 i = 0; i != 7; ++i) {
		emerald_mask[i] = (HM_global.currentSave->superEmeralds & 1 << i) ? '1' : '0';
	}
	sprintf(
		str,
		"emeralds %stransfered, current mask: %.7s",
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
		RSDK.PrintLog(PRINT_ERROR, "[HyperMania] failed to save persistent data");
		return;
	}
	RSDK.PrintLog(PRINT_NORMAL, "[HyperMania] persistent data saved");

	if (!HM_global.currentSave) return;
	char save_message[SAVEMSG_LEN];
	HM_Save_FormatString(save_message);
	RSDK.PrintLog(PRINT_NORMAL, "[HyperMania] save info: %s", save_message);
}

static void HM_Save_LoadCB(int32 status) {
#if MANIA_USE_PLUS
	const bool32 success = (status == STATUS_OK || status == STATUS_NOTFOUND) ? true : false;
#else
	const bool32 success = (status) ? true : false;
#endif
	if (!success) {
		RSDK.PrintLog(PRINT_ERROR, "[HyperMania] failed to load persistent data");
		return;
	}
	RSDK.PrintLog(PRINT_NORMAL, "[HyperMania] persistent data loaded");

	if (!HM_global.currentSave) return;
	char save_message[SAVEMSG_LEN];
	HM_Save_FormatString(save_message);
	RSDK.PrintLog(PRINT_NORMAL, "[HyperMania] save info: %s", save_message);
}


HM_SaveRAM* HM_Save_GetDataPtr(int32 slot, bool32 encore) {
	if (encore) return &HM_global.saveRAM[slot % 3 + 8];
	else        return &HM_global.saveRAM[slot % 8];
	return &HM_global.noSaveSlot;
}

void HM_Save_SaveFile() {
	API.SaveUserFile(SAVE_FILE_NAME, &HM_global.saveRAM, sizeof(HM_global.saveRAM), HM_Save_SaveCB, false);
}

void HM_Save_LoadFile() {
	API.LoadUserFile(SAVE_FILE_NAME, &HM_global.saveRAM, sizeof(HM_global.saveRAM), HM_Save_LoadCB);
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
		RSDK.PrintLog(PRINT_ERROR, "[HyperMania] max extended memory objects already reached");
		return NULL;
	}
	if (owner_id >= ENTITY_COUNT - TEMPENTITY_COUNT) {
		RSDK.PrintLog(PRINT_ERROR, "[HyperMania] temporary entitities are invalid");
		return NULL;
	}

	int32 id = 0;
	while (ExtMemoryRevIndex[id] != EXTMEM_FREE_ID) ++id;
	ExtMemoryRevIndex[id] = owner_id;
	ExtMemoryIndex[owner_id] = id;

	if (!ExtMemory[id].mem) {
		ExtMemory[id].mem = malloc(bytes);
	} else if (bytes != ExtMemory[id].size) {
		ExtMemory[id].mem = realloc(ExtMemory[id].mem, bytes);
	}
	ExtMemory[id].size = bytes;
	++ExtMemory_size;
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