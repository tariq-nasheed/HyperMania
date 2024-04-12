#pragma once

#define DRAGONFLY_SPINE_COUNT (6)

struct ObjectDragonfly {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxSpine;
	uint16 aniFrames;
};

struct EntityDragonfly {
	RSDK_ENTITY
	StateMachine(state);
	uint8 dir;
	uint8 dist;
	uint8 speed;
	Vector2 positions[DRAGONFLY_SPINE_COUNT];
	uint8 directions[DRAGONFLY_SPINE_COUNT];
	Vector2 startPos;
	Animator animator;
	Animator wingAnimator;
	Animator bodyAnimator;
};
