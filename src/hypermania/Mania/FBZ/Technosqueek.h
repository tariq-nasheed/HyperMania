#pragma once

struct ObjectTechnosqueek {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
};

struct EntityTechnosqueek {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	uint8 speed;
	uint16 distance;
	uint8 distRemain;
	int32 acceleration;
	int32 targetVel;
	int32 tailOffset;
	bool32 shouldTurn;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
	Animator tailAnimator;
};
