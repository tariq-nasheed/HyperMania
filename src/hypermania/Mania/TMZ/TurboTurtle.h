#pragma once

struct ObjectTurboTurtle {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
	uint16 sfxWalk;
	uint16 sfxWalk2;
};

struct EntityTurboTurtle {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	int32 timer;
	Animator animator;
	uint8 currentSide;
	uint16 stepTimer;
	Hitbox hitboxFanT;
	Hitbox hitboxFanR;
	Hitbox hitboxFanL;
	bool32 fanActiveTop;
	bool32 rightFanActive;
	bool32 leftFanActive;
	uint16 stepCount;
	uint8 initialSide;
	bool32 stationary;
	uint8 leftFanDir;
	int32 leftFanDuration;
	int32 leftFanStrength;
	int32 leftFanLength;
	uint8 rightFanDir;
	int32 rightFanDuration;
	int32 rightFanStrength;
	int32 rightFanLength;
};
