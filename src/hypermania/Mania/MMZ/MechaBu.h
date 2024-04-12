#pragma once

struct ObjectMechaBu {
	RSDK_OBJECT
	TABLE(int32 sawOffsets[10], { -0x150000, -0xF0000, -0x170000, -0xE0000, -0x190000, -0xA0000, -0x1A0000, -0x50000, -0x1A0000, -0x40000 });
	Hitbox hitboxSaw;
	Hitbox hitboxUnused;
	uint16 aniFrames;
	uint16 sfxSawUp;
	uint16 sfxSawDown;
};

struct EntityMechaBu {
	RSDK_ENTITY
	StateMachine(state);
	ManiaPlaneFilterTypes planeFilter;
	uint8 timer;
	uint8 sawTimer;
	Vector2 startPos;
	uint8 startDir;
	Vector2 sawPos;
	Animator badnikAnimator;
	Animator hornAnimator;
	Animator sawAnimator;
};
