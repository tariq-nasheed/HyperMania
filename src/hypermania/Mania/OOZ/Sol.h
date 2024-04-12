#pragma once

#define SOL_FLAMEORB_COUNT (4)

struct ObjectSol {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxOrb;
	uint16 aniFrames;
};

struct EntitySol {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	uint8 activeOrbs;
	Vector2 positions[SOL_FLAMEORB_COUNT];
	int32 oscillateAngle;
	bool32 isFlameFX;
	bool32 fireOrbs;
	Animator mainAnimator;
	Animator ballAnimator;
};
