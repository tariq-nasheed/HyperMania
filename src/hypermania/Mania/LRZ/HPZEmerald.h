#pragma once

typedef enum {
	HPZEMERALD_MASTER,
	HPZEMERALD_EMERALD_LOW,
	HPZEMERALD_EMERALD_HIGH,
} HPZEmeraldTypes;

struct ObjectHPZEmerald {
	RSDK_OBJECT
	uint16 aniFrames;
};

struct EntityHPZEmerald {
	RSDK_ENTITY
	StateMachine(state); // unused
	uint8 type;
	bool32 solid;
	Vector2 startPos;
	Hitbox *hitbox;
	Animator emeraldAnimator;
	Animator overlayAnimator;
};
