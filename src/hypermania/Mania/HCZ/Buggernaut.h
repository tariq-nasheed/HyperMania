#pragma once

struct ObjectBuggernaut {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxParentRange;
	uint16 aniFrames;
};

struct EntityBuggernaut {
	RSDK_ENTITY
	StateMachine(state);
	bool32 passThrough;
	int32 timer;
	int32 buzzCount;
	Vector2 startPos;
	Entity* parent;
	Animator bodyAnimator;
	Animator wingAnimator;
};
