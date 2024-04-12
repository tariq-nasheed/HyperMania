#pragma once

struct ObjectMicDrop {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxElectrify;
};

struct EntityMicDrop {
	RSDK_ENTITY
	StateMachine(state);
	Animator bodyAnimator;
	Animator wireAnimator;
	Vector2 startPos;
	uint16 distance;
	int32 timer;
	int32 swingSpeed;
	int32 swingVel;
	int32 radius;
	int32 swingPos;
};
