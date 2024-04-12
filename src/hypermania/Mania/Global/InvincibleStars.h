#pragma once

// Object Class
struct ObjectInvincibleStars {
	RSDK_OBJECT
	uint16 aniFrames;
};

// Entity Class
struct EntityInvincibleStars {
	RSDK_ENTITY
	EntityPlayer* player;
	Vector2 starPos[8];
	int32 starAngle[2];
	int32 starFrame[2];
	int32 starOffset;
	Animator starAnimator[4];
};
