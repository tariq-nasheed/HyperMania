#pragma once

#define HATTERKILLER_SEGMENT_COUNT (10)

struct ObjectHatterkiller {
	RSDK_OBJECT
	Hitbox hitboxSegment;
	uint16 sfxRocketJet;
	uint16 sfxTransform2;
	uint16 sfxPowerup;
	uint16 aniFrames;
};

struct EntityHatterkiller {
	RSDK_ENTITY
	int32 timer;
	Vector2 bodyPositions[HATTERKILLER_SEGMENT_COUNT];
	Vector2 bodyVelocities[HATTERKILLER_SEGMENT_COUNT];
	int32 bodyDelays[HATTERKILLER_SEGMENT_COUNT];
	Animator* bodyAnimators[HATTERKILLER_SEGMENT_COUNT];
	Animator headAnimator;
	Animator bodyAnimator;
	Animator tailAnimator;
};
