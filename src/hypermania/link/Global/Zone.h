#pragma once

extern ObjectZone* Zone;
extern int32 (*Zone_GetZoneID)();
extern void (*Zone_StartFadeIn)(int32, int32);
extern void (*Zone_StartFadeOut)(int32, int32);