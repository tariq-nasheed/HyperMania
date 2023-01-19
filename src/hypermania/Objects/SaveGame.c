#include "SaveGame.h"

HM_SaveRam* localHM_SaveRam;
HM_SaveRam globalHM_SaveRam[11];
SaveRAM* (*SaveGame_GetSaveRAM)(void);