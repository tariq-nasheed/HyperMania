#ifndef OBJ_SAVEGAME_H
#define OBJ_SAVEGAME_H

#include "GameAPI/Game.h"

typedef enum {
	SAVEGAME_BLANK,
	SAVEGAME_INPROGRESS,
	SAVEGAME_COMPLETE,
} SaveGameStates;

typedef enum {
	SAVERECALL_NORMAL,
	SAVERECALL_DISABLED,
	SAVERECALL_BROKENITEMBOX,
} SaveRecallStates;

typedef struct {
	uint8 padding[0x58];
	int32 saveState;
	int32 characterID;
	int32 zoneID;
	int32 lives;
	int32 score;
	int32 score1UP;
	int32 chaosEmeralds;
	int32 continues;
	int32 storedStageID;
	int32 nextSpecialStage;
	int32 collectedSpecialRings;
	int32 medalMods;
#if MANIA_USE_PLUS
	int32 zoneTimes[32];
	int32 characterFlags;
	int32 stock;
	int32 playerID;
#endif
} SaveRAM;

extern SaveRAM* (*SaveGame_GetSaveRAM)(void);
extern void (*SaveGame_SaveGameState)(void);
extern int32* (*SaveGame_GetDataPtr)(int32 slot, bool32 encore);
extern SaveRAM* GetSaveRAM_Safe(); // this really shouldnt be here but whatever

#define OBJ_SAVE_SETUP \
  IMPORT_PUBLIC_FUNC(SaveGame_GetSaveRAM); \
  IMPORT_PUBLIC_FUNC(SaveGame_SaveGameState); \
  IMPORT_PUBLIC_FUNC(SaveGame_GetDataPtr)

#endif //! OBJ_SAVEGAME_H
