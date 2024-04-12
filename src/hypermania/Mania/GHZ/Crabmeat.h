#pragma once

struct ObjectCrabmeat {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
};

struct EntityCrabmeat {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	uint8 shootState;
	Vector2 startPos;
	int32 startDir;
	Animator animator;
};
