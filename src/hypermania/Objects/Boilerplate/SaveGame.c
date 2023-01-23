#include "SaveGame.h"

SaveRAM* (*SaveGame_GetSaveRAM)(void);
void (*SaveGame_SaveGameState)(void);