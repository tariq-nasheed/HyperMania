#pragma once

struct ObjectCanista {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxDetect;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
	uint16 sfxPon;
};

struct EntityCanista {
	RSDK_ENTITY
	StateMachine(state);
	uint8 triggerMode;
	Vector2 detectOffset;
	Vector2 detectSize;
	int32 shootOffset;
	int32 shootSize;
	int32 stopTimer;
	int32 detectDelay;
	EntityPlayer* detectedPlayer;
	Vector2 startPos;
	uint8 startDir;
	uint8 moveDir;
	uint8 timer;
	Hitbox hitboxDetect;
	int32 unused1;
	int32 unused2;
	Animator mainAnimator;
	Animator tapeAnimator;
	Animator cannonAnimator;
};
