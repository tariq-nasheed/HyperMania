#ifndef OBJ_ZONE_H
#define OBJ_ZONE_H

#include "GameAPI/Game.h"

extern ObjectZone *Zone;
extern int32 (*Zone_GetZoneID)(void);
extern void (*Zone_StartFadeIn)(int32, int32);
extern void (*Zone_StartFadeOut)(int32, int32);

#endif //! OBJ_ZONE_H
