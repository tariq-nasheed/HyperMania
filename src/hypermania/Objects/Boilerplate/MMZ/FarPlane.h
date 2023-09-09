#ifndef OBJ_FARPLANE_H
#define OBJ_FARPLANE_H

#include "GameAPI/Game.h"

#define FARPLANE_ENTITY_COUNT (256)

typedef struct {
	RSDK_OBJECT
	uint32 aniFrames;
	Vector2 screenPos;
	Vector2 worldPos;
	Vector2 originPos;
	Vector2 position;
	Vector2 positionList[0x200];
	int32 unused1;
	int32 unused2;
	int32 unused3;
	int32 unused4;
	int32 unused5;
	uint16 layerID;
} ObjectFarPlane;

typedef struct {
	RSDK_ENTITY
	Vector2 size;
	Vector2 origin;
	uint16 entitySlots[FARPLANE_ENTITY_COUNT];
	int32 entityCount;
	Animator animator;
} EntityFarPlane;

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
