#pragma once

struct ObjectScarab {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxGrab;
	uint16 aniFrames;
};

struct EntityScarab {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	Vector2 moveOffset;
	uint8 startDir;
	int32 timer;
	int32 playerTimers[PLAYER_COUNT];
	Animator bodyAnimator;
	Animator frontLegAnimator;
	Animator backLegAnimator;
	int32 amplitude;
	uint8 childCount;
	ManiaPlaneFilterTypes planeFilter;
	uint8 drawGroupLow;
	uint8 drawGroupHigh;
	uint8 pullCount;
	int8 moveDir;
	uint8 grabbedPlayers;
};
