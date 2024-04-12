#pragma once

struct ObjectBuzzBomber {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
};

struct EntityBuzzBomber {
	RSDK_ENTITY
	StateMachine(state);
	uint8 shotRange;
	int32 timer;
	uint8 detectedPlayer;
	Vector2 startPos;
	uint8 startDir;
	Entity *projectile;
	Animator animator;
	Animator wingAnimator;
	Animator thrustAnimator;
	Hitbox hitboxRange;
};
