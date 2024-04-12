#pragma once

struct ObjectOctus {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxProjectile;
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxShot;
};

struct EntityOctus {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	uint8 unused1;
	Vector2 startPos;
	uint8 startDir;
	int32 unused2;
	Animator animator;
};
