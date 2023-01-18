#ifndef UTIL_H
#define UTIL_H

#include "GameAPI/Game.h"

// =============================================================================

// Extension variables for preexisting objects ---------------------------------

// =============================================================================
#define EXTMEM_FREE_ID -1
#define MAX_EXTMEM_ENTITIES 64

typedef struct {
	int32 owner_id;
	uint32 size;
	void* mem;
} extmem_t;
extern extmem_t ExtMemory[MAX_EXTMEM_ENTITIES];
extern uint32   ExtMemory_size;

extern void* AllocExtMem(int32 owner_id, uint32 bytes);
extern void* GetExtMem(int32 owner_id);
extern void FreeExtMem(int32 owner_id);

#endif