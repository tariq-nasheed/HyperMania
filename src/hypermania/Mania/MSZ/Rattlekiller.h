#pragma once

#define RATTLEKILLER_SEGMENT_COUNT (10)

struct ObjectRattlekiller {
	RSDK_OBJECT
	Hitbox hitboxSegment;
	uint16 sfxRocketJet;
	uint16 aniFrames;
};

struct EntityRattlekiller {
	RSDK_ENTITY
	StateMachine(state);     // Unused
	StateMachine(stateDraw); // Unused
	int32 timer;
	int32 bodyStates[RATTLEKILLER_SEGMENT_COUNT];
	Vector2 bodyPositions[RATTLEKILLER_SEGMENT_COUNT];
	Vector2 bodyOriginPos[RATTLEKILLER_SEGMENT_COUNT];
	Vector2 bodyVelocities[RATTLEKILLER_SEGMENT_COUNT];
	int32 bodyAngles[RATTLEKILLER_SEGMENT_COUNT];
	int32 bodyDepth[RATTLEKILLER_SEGMENT_COUNT];
	int32 bodyDelays[RATTLEKILLER_SEGMENT_COUNT];
	int32 bodyIDs[RATTLEKILLER_SEGMENT_COUNT];
	Animator* bodyAnimators[RATTLEKILLER_SEGMENT_COUNT];
	Vector2 topBounds;
	Vector2 bottomBounds;
	Vector2 targetPos;
	int32 length;
	Animator headAnimator;
	Animator bodyAnimator;
	Animator tailAnimator;
};
