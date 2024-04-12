#pragma once

// Constants
#define IMAGETRAIL_TRACK_COUNT (7)

// Object Class
struct ObjectImageTrail {
	RSDK_OBJECT
};

// Entity Class
struct EntityImageTrail {
	RSDK_ENTITY
	EntityPlayer *player;
	int32 playerClassID;
	Vector2 currentPos;
	Vector2 statePos[IMAGETRAIL_TRACK_COUNT];
	int32 currentRotation;
	int32 stateRotation[IMAGETRAIL_TRACK_COUNT];
	uint8 currentDirection;
	uint8 stateDirection[IMAGETRAIL_TRACK_COUNT];
	uint8 currentVisible;
	uint8 stateVisible[IMAGETRAIL_TRACK_COUNT];
	int32 currentScale;
	int32 stateScale[IMAGETRAIL_TRACK_COUNT];
	Animator currentAnimator;
	Animator stateAnimator[IMAGETRAIL_TRACK_COUNT];
	int32 baseAlpha;
	int32 fadeoutTimer;
};