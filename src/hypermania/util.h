#ifndef UTIL_H
#define UTIL_H

#include "GameAPI/Game.h"

extern bool32 HPZ_SuperSpecialStage; // bad hack variable for testing purposes, will be removed later, please understand
// =============================================================================

// Helper macros ---------------------------------------------------------------

// =============================================================================
#define IMPORT_PUBLIC_FUNC(name) \
  name = Mod.GetPublicFunction(NULL, #name); \
  if (name == NULL) RSDK.PrintLog(PRINT_ERROR, "[HyperMania] "#name" is not a public function\n")
#define HOOK_STATE(name, priority) \
  void (*name##_fn) = Mod.GetPublicFunction(NULL, #name); \
  if (name##_fn == NULL) RSDK.PrintLog(PRINT_ERROR, "[HyperMania] "#name" is not a public function\n"); \
  else Mod.RegisterStateHook(name##_fn, name##_HOOK, priority)
#define HOOK_IMPORTED_STATE(name, priority) Mod.RegisterStateHook(name, name##_HOOK, priority)

// =============================================================================

// Save games ------------------------------------------------------------------

// =============================================================================
#define SAVE_FILE_NAME "HyperManiaSaveData.bin"

typedef struct {
	uint32 transferedEmeralds;
	uint32 superEmeralds;
} HM_SaveRAM;

HM_SaveRAM* HM_Save_GetDataPtr(int32 slot, bool32 encore);
void HM_Save_SaveFile();
void HM_Save_LoadFile();

// =============================================================================

// Globals ---------------------------------------------------------------------

// =============================================================================
typedef struct {
	HM_SaveRAM saveRAM[11];
	HM_SaveRAM noSaveSlot;
	HM_SaveRAM* currentSave;
} HM_global_t;

extern HM_global_t HM_global;

// =============================================================================

// Extension variables for preexisting objects ---------------------------------

// =============================================================================
#define EXTMEM_FREE_ID -1
#define MAX_EXTMEM_ENTITIES 64

typedef struct {
	size_t size;
	void* mem;
} extmem_t;
extern extmem_t     ExtMemory[MAX_EXTMEM_ENTITIES];
extern uint32       ExtMemory_size;
extern int8 ExtMemoryIndex[ENTITY_COUNT - TEMPENTITY_COUNT];
extern int8 ExtMemoryRevIndex[MAX_EXTMEM_ENTITIES];

void* AllocExtMem(int32 owner_id, uint32 bytes);
void* GetExtMem(int32 owner_id);
void FreeExtMem(int32 owner_id);

#endif //! UTIL_H