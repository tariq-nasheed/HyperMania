#pragma once

struct ObjectBumpalo {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxBumper;
	Hitbox hitboxRange;
	Hitbox hitboxCharge;
	Hitbox hitboxUnused;
	uint16 aniFrames;
	uint16 sfxBumper;
	uint16 sfxHuff;
	uint16 sfxClack;
	uint16 sfxImpact;
};

struct EntityBumpalo {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	int32 timer;
	bool32 ignoreCliffs;
	bool32 wallCollided;
	Animator badnikAnimator;
	Animator huffAnimator;
	Animator dustAnimator;
};
