#pragma once

#define REXON_SEGMENT_COUNT (5)

typedef enum {
	REXON_MAIN,
	REXON_DEBRIS,
	REXON_SHOT,
} RexonTypes;

struct ObjectRexon {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxShell;
	Hitbox hitboxRange;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
	uint16 sfxShot;
	uint16 sfxExplosion;
};

struct EntityRexon {
	RSDK_ENTITY
	StateMachine(state);
	bool32 noMove;
	int32 type;
	Vector2 startPos;
	uint8 startDir;
	Vector2 positions[REXON_SEGMENT_COUNT + 1]; // neck + head
	int32 segmentMagnitude[REXON_SEGMENT_COUNT];
	int32 segmentAmplitude[REXON_SEGMENT_COUNT];
	uint8 segmentDirections[REXON_SEGMENT_COUNT];
	uint8 segmentID;
	int32 timer;
	int32 destroyDelay;
	Animator bodyAnimator;
	Animator neckAnimator;
	Animator headAnimator;
};
