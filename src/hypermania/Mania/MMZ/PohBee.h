#pragma once

struct ObjectPohBee {
	RSDK_OBJECT
	Hitbox hitbox;
	uint16 aniFrames;
};

struct EntityPohBee {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	int32 chainPos[2];
	int32 chainAngle[2];
	int32 unused;
	bool32 isTurning;
	Animator bodyAnimator;
	Animator wingsAnimator;
	Animator chainAnimator;
	Animator spikeAnimator;
	Hitbox hitboxes[2];
	uint8 spikeCount;
	Vector2 amplitude;
	ManiaPlaneFilterTypes planeFilter;
};
