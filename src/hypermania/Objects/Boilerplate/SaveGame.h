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

extern SaveRAM* (*SaveGame_GetSaveRAM)(void);
extern void (*SaveGame_SaveGameState)(void);
extern int32* (*SaveGame_GetDataPtr)(int32 slot, bool32 encore);

#define OBJ_SAVE_SETUP \
  IMPORT_PUBLIC_FUNC(SaveGame_GetSaveRAM); \
  IMPORT_PUBLIC_FUNC(SaveGame_SaveGameState); \
  IMPORT_PUBLIC_FUNC(SaveGame_GetDataPtr)

#endif //! OBJ_SAVEGAME_H
