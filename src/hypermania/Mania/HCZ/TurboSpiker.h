#pragma once

struct ObjectTurboSpiker {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxSpike;
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxLaunch;
	uint16 sfxSplash;
};

struct EntityTurboSpiker {
	RSDK_ENTITY
	StateMachine(state);
	uint32 type;
	int32 timer;
	int32 unused;
	Vector2 startPos;
	uint8 startDir;
	Entity* spike;
	Animator shellAnimator;
	Animator animator;
	bool32 playedLaunchSfx;
};
