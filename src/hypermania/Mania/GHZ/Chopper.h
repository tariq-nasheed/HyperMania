#pragma once

struct ObjectChopper {
	RSDK_OBJECT
	Hitbox hitboxJump;
	Hitbox hitboxSwim;
	Hitbox hitboxRange;
	Hitbox hitboxWater;
	uint16 aniFrames;
};

struct EntityChopper {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	uint16 timer;
	bool32 charge;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
};
