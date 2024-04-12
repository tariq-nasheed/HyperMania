#pragma once

struct ObjectKabasira {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Vector2 onScreenRange;
	uint16 aniFrames;
	uint16 sfxPon;
	uint16 sfxExplosion2;
};

struct EntityKabasira {
	RSDK_ENTITY
	StateMachine(state);
	int32 unused1;
	int32 unused2;
	Vector2 startPos;
	uint8 startDir;
	int32 timer;
	Animator bodyAnimator;
	Animator wingsAnimator;
	int32 unused3;
};
