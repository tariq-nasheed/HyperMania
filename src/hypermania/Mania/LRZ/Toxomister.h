#pragma once

struct ObjectToxomister {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxCloud;
	uint16 aniFrames;
};

struct EntityToxomister {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	Entity* parent;
	EntityPlayer* grabbedPlayer;
	int32 timer;
	uint16 shakeTimer;
	uint16 shakeCount;
	uint16 prevShakeFlags;
	Animator animator;
};
