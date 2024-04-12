#pragma once

struct ObjectSpiny {
	RSDK_OBJECT
	Hitbox hitboxSpiny;
	Hitbox hitboxRange;
	Hitbox hitboxShot;
	uint16 aniFrames;
	uint16 sfxShot;
};

struct EntitySpiny {
	RSDK_ENTITY
	StateMachine(state);
	Animator animator;
	int32 unused;
	uint8 type;
	Vector2 startPos;
	uint8 startDir;
	int32 shotVelocity;
	int32 dirChangeTimer;
	int32 moveTimer;
};
