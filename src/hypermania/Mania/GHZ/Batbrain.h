#pragma once

struct ObjectBatbrain {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
	uint16 sfxFlap;
};

struct EntityBatbrain {
	RSDK_ENTITY
	StateMachine(state);
	int32 targetY;
	EntityPlayer* target;
	Vector2 startPos;
	Animator animator;
};
