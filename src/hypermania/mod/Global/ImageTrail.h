#pragma once

// =============================================================================

// Definitions -----------------------------------------------------------------

// =============================================================================
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