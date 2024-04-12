#pragma once

struct ObjectWoodrow {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxFullRange;
	Hitbox hitboxBombRange;
	Hitbox hitboxBomb;
	uint16 aniFrames;
	uint16 sfxExplosion;
	uint16 sfxPeck;
};

struct EntityWoodrow {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	int32 distUp;
	int32 distDown;
	uint8 activeBombCount;
	uint8 bombCount;
	uint8 bombFallDelay;
	uint8 moveDelay;
	int32 rangeMask;
	Vector2 startPos;
	uint8 startDir;
	void* parent;
	Animator animator;
};
