#pragma once

struct ObjectIceBomba {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxBomb;
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxExplosion;
	uint16 sfxFreeze;
};

struct EntityIceBomba {
	RSDK_ENTITY
	StateMachine(state);
	uint8 dir;
	uint16 dist;
	uint16 dip;
	uint8 startDir;
	Vector2 startPos;
	uint32 startDist;
	Animator bodyAnimator;
	Animator wingAnimator;
	Animator bombAnimator;
};
