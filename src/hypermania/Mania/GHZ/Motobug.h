#pragma once

struct ObjectMotobug {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
};

struct EntityMotobug {
	RSDK_ENTITY
	StateMachine(state);
	int32 turnTimer;
	int32 timer;
	Vector2 startPos;
	uint8 startDir;
	bool32 wasTurning;
	Animator animator;
};
