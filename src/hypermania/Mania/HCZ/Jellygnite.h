#pragma once

struct ObjectJellygnite {
	RSDK_OBJECT
	Hitbox hitbox;
	Hitbox hitboxUnused;
	uint16 aniFrames;
	uint16 sfxGrab;
	uint16 sfxElectrify;
};

struct EntityJellygnite {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	uint8 timer;
	uint8 grabDelay;
	int32 frontTentacleAngle;
	int32 oscillateAngle;
	EntityPlayer* grabbedPlayer;
	uint8 shakeTimer;
	uint8 shakeCount;
	uint8 lastShakeFlags;
	uint8 prevAnimationID;
	Animator bodyAnimator;
	Animator frontTentacleAnimator;
	Animator backTentacleAnimator;
};
