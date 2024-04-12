#pragma once

#define FARPLANE_ENTITY_COUNT (256)

struct ObjectFarPlane {
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
};

struct EntityFarPlane {
	RSDK_ENTITY
	Vector2 size;
	Vector2 origin;
	uint16 entitySlots[FARPLANE_ENTITY_COUNT];
	int32 entityCount;
	Animator animator;
};
