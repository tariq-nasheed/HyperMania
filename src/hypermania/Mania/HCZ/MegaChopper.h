#pragma once

struct ObjectMegaChopper {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxChop;
	uint16 aniFrames;
};

struct EntityMegaChopper {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	EntityPlayer* grabbedPlayer;
	Vector2 playerPos;
	uint8 playerDir;
	uint16 shakeTimer;
	uint16 shakeCount;
	uint16 lastShakeFlags;
	uint8 nibbleTimer;
	Animator animator;
};
