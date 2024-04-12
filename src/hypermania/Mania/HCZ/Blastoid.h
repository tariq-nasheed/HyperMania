#pragma once

struct ObjectBlastoid {
	RSDK_OBJECT
	Hitbox hitboxBody;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
	uint16 sfxShot;
};

struct EntityBlastoid {
	RSDK_ENTITY
	StateMachine(state);
	uint8 timer;
	Animator animator;
};
