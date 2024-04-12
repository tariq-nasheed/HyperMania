#pragma once

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
