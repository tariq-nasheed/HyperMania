#pragma once

struct ObjectBlaster {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
};

struct EntityBlaster {
	RSDK_ENTITY
	StateMachine(state);
	uint16 unused1;
	uint16 timer;
	uint16 attackTimer;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
};
