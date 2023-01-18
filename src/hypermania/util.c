#include "util.h"

extmem_t ExtMemory[MAX_EXTMEM_ENTITIES];
uint32   ExtMemory_size;


void* AllocExtMem(int32 owner_id, uint32 bytes) {
	if (ExtMemory_size == MAX_EXTMEM_ENTITIES) {
		printf("ERROR: max extended memory objects already reached\n");
		return NULL;
	}

	int32 id = 0;
	while (ExtMemory[id].owner_id != EXTMEM_FREE_ID) ++id;

	ExtMemory[id].owner_id = owner_id;
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
	for (int32 i = 0; i != ExtMemory_size; ++i) {
		if (ExtMemory[i].owner_id == owner_id) return ExtMemory[i].mem;
	}
	return NULL;
}

void FreeExtMem(int32 owner_id) {
	for (int32 i = 0; i != ExtMemory_size; ++i) {
		if (ExtMemory[i].owner_id == owner_id) ExtMemory[i].owner_id = EXTMEM_FREE_ID;
	}
	--ExtMemory_size;
}