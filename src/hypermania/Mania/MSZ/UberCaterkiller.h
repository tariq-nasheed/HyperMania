#pragma once

#define UBERCATERKILLER_SEGMENT_COUNT (10)

struct ObjectUberCaterkiller {
	RSDK_OBJECT
	Hitbox hitboxSegment;
	bool32 defeated;
	uint16 sfxRocketJet;
	uint16 sfxHit;
	uint16 sfxExplosion2;
	uint16 sfxExplosion3;
	uint16 sfxSandSwim;
	uint16 sfxBumper3;
	uint16 sfxCaterJump;
	uint16 aniFrames;
};

struct EntityUberCaterkiller {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	Vector2 bodyPositions[UBERCATERKILLER_SEGMENT_COUNT];
	Vector2 bodyVelocity[UBERCATERKILLER_SEGMENT_COUNT];
	int32 bodyTimers[UBERCATERKILLER_SEGMENT_COUNT];
	int32 bodyScales[UBERCATERKILLER_SEGMENT_COUNT];
	int32 bodyInAir[UBERCATERKILLER_SEGMENT_COUNT];
	int32 bodyAngles[UBERCATERKILLER_SEGMENT_COUNT];
	Animator* bodyAnimators[UBERCATERKILLER_SEGMENT_COUNT];
	uint8 aniID;
	uint8 jumpsRemain;
	int32 targetScale;
	int32 targetBodyPos;
	uint8 playerTimers[PLAYER_COUNT];
	Animator headAnimator;
	Animator bodyAnimator;
};
