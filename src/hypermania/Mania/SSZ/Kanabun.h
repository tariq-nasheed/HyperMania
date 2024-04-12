#pragma once

struct ObjectKanabun {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
};

struct EntityKanabun {
	RSDK_ENTITY
	StateMachine(state);
	int32 unused;
	Vector2 startPos;
	uint8 startDir;
	int32 hVel;
	uint8 hDist;
	uint8 bobDist;
	uint8 angleVel;
	Animator animator;
};
