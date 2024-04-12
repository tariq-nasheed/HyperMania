#pragma once

struct ObjectVultron {
	RSDK_OBJECT
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxVultron;
};

struct EntityVultron {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	Vector2 startPos;
	uint8 startDir;
	uint16 dist;
	uint16 distRemain;
	int32 storeY;
	Hitbox hitboxBadnik;
	Animator bodyAnimator;
	Animator flameAnimator;
};
