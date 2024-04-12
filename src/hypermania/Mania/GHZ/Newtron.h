#pragma once

struct ObjectNewtron {
	RSDK_OBJECT
	Hitbox hitboxShoot;
	Hitbox hitboxFly;
	Hitbox hitboxProjectile;
	Hitbox hitboxRange;
	uint16 aniFrames;
};

struct EntityNewtron {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	int32 timer;
	Vector2 startPos;
	Animator animator;
	Animator flameAnimator;
};
