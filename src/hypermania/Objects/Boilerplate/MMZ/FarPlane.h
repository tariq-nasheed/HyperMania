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

extern ObjectFarPlane *FarPlane;

#endif //! OBJ_FARPLANE_H
