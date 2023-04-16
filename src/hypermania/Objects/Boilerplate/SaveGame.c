#include "SaveGame.h"

SaveRAM* (*SaveGame_GetSaveRAM)(void);
void (*SaveGame_SaveGameState)(void);

SaveRAM* GetSaveRAM_Safe() {
	if (SaveGame_GetSaveRAM()) return SaveGame_GetSaveRAM();
	return (SaveRAM*)((globals->saveSlotID == NO_SAVE_SLOT) ? globals->noSaveSlot : SaveGame_GetDataPtr(globals->saveSlotID));
}