#pragma once

struct ObjectSplats {
	RSDK_OBJECT
	StateMachine(initialState);
	Hitbox hitboxBadnikGHZ;
	Hitbox hitboxJar;
	Hitbox hitboxBadnikPGZ;
	uint16 aniFrames;
	uint16 sfxSplatsSpawn;
	uint16 sfxSplatsLand;
};

struct EntitySplats {
	RSDK_ENTITY
	StateMachine(state);
	uint8 bounceCount;
	uint8 activeCount;
	uint8 numActive;
	uint16 minDelay;
	int32 delay;
	bool32 isOnScreen;
	Entity* parent; // all pointer types are the same size who gives a shit
	Vector2 startPos;
	int32 startDir;
	Animator mainAnimator;
	Animator splashAnimator;
};
