#pragma once

struct ObjectDebris {
	RSDK_OBJECT
};

struct EntityDebris {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	int32 gravityStrength;
	int32 rotSpeed;
	Vector2 scaleSpeed;
	int32 delay;
	Animator animator;
};