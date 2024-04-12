#pragma once

struct ObjectPhantomShinobi {
	RSDK_OBJECT
	Hitbox hitbox;
	uint16 aniFrames;
	uint16 sfxBlade;
	uint16 sfxHit;
};

struct EntityPhantomShinobi {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	int32 timer;
	int32 invincibilityTimer;
	int32 unused;
	int32 finRadius;
	int32 rotStore;
	int32 rotSpeed;
	int32 numBounces;
	int32 attackCount;
	bool32 prevOnGround;
	Hitbox outerBox;
	Hitbox innerBox;
	Animator bodyAnimator;
	Animator armAnimator;
	Animator finAnimator;
};
