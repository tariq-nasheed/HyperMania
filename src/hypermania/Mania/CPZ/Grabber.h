#pragma once

struct ObjectGrabber {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxGrab;
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxGrab;
	uint16 sfxDestroy;
};

struct EntityGrabber {
	RSDK_ENTITY
	StateMachine(state);
	Animator bodyAnimator;
	Animator clampAnimator;
	Animator wheelAnimator;
	EntityPlayer* grabbedPlayer;
	uint16 struggleDelay;
	uint16 struggleTimer;
	uint16 struggleFlags;
	uint16 grabDelay;
	Vector2 startPos;
	uint8 startDir;
	int32 turnTimer;
	int32 timer;
};
