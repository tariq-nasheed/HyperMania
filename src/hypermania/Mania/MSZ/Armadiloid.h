#pragma once

struct ObjectArmadiloid {
	RSDK_OBJECT
	uint16 aniFrames;
	uint16 sfxShot;
};

struct EntityArmadiloid {
	RSDK_ENTITY
	StateMachine(state);
	int32 type;
	int32 timer;
	Entity* child;
	Entity* parent;
	Vector2 startPos;
	Hitbox hitbox;
	Animator bodyAnimator;
	Animator headAnimator;
	Animator boosterAnimator;
};
