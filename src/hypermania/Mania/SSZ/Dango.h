#pragma once

struct ObjectDango {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxCurlRange;
	uint16 aniFrames;
	uint16 sfxBumper;
};

struct EntityDango {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	int32 rollDelay;
	bool32 preventStateChange;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
};
