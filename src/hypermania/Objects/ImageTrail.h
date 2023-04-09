#ifndef OBJ_IMAGETRAIL_H
#define OBJ_IMAGETRAIL_H

#include "GameAPI/Game.h"

// =============================================================================

// Definitions -----------------------------------------------------------------

// =============================================================================
// Constants
#define IMAGETRAIL_TRACK_COUNT (7)

// Object Class
typedef struct {
	RSDK_OBJECT
} ObjectImageTrail;

// Entity Class
typedef struct {
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
} EntityImageTrail;

// Object Struct
extern ObjectImageTrail *ImageTrail;

// =============================================================================

// Mod Definitions -------------------------------------------------------------

// =============================================================================
typedef struct {
	Vector2 statePos[1];
	int32 stateRotation[1];
	uint8 stateDirection[1];
	uint8 stateVisible[1];
	int32 stateScale[1];
	Animator stateAnimator[1];
} ImageTrailExt;

// =============================================================================

// Functions -------------------------------------------------------------------

// =============================================================================
void ImageTrail_Create_OVERLOAD(void* data);
void ImageTrail_Draw_OVERLOAD();
void ImageTrail_LateUpdate_OVERLOAD();

#endif //! OBJ_IMAGETRAIL_H
