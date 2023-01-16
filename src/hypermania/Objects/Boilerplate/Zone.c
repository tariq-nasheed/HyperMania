#include "Zone.h"

ObjectZone *Zone;
int32 (*Zone_GetZoneID)(void);
void (*Zone_StartFadeIn)(int32, int32);
void (*Zone_StartFadeOut)(int32, int32);