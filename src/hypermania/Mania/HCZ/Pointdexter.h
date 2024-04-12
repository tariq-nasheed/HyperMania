#pragma once

struct ObjectPointdexter {
	RSDK_OBJECT
	Hitbox hitbox;
	uint16 aniFrames;
};

struct EntityPointdexter {
	RSDK_ENTITY
	StateMachine(state);
	uint8 timer;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
};
