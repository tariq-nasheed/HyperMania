#ifndef OBJ_FARPLANE_H
#define OBJ_FARPLANE_H

#include "GameAPI/Game.h"

extern ObjectFarPlane* FarPlane;

extern void (*FarPlane_SetupEntities)();
extern void (*FarPlane_SetEntityActivities)(uint8 active);

void FarPlane_LateUpdate_OVERLOAD();

void FarPlane_DrawHook_ApplyFarPlane();
void FarPlane_DrawHook_RemoveFarPlane();

#define OBJ_FARPLANE_SETUP \
  IMPORT_PUBLIC_FUNC(FarPlane_SetupEntities); \
  IMPORT_PUBLIC_FUNC(FarPlane_SetEntityActivities); \
  MOD_REGISTER_OBJ_OVERLOAD(FarPlane, NULL, FarPlane_LateUpdate_OVERLOAD, NULL, NULL, NULL, NULL, NULL, NULL, NULL)

#endif //! OBJ_FARPLANE_H
