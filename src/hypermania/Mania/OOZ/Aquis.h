#pragma once

struct ObjectAquis {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
	uint16 sfxShot;
};

struct EntityAquis {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	uint8 playerInRange;
	int32 remainingTurns;
	Vector2 startPos;
	uint8 startDir;
	Animator mainAnimator;
	Animator wingAnimator;
};
