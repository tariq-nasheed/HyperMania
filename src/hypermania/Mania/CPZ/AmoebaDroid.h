#pragma once

#define AMOEBADROID_BLOB_COUNT (8)

struct ObjectAmoebaDroid {
	RSDK_OBJECT
	TABLE(int32 debrisInfo1[17], { 4, 0, 0, -0x20000, -0x28000, 1, 0, 0x20000, -0x28000, 2, 0, -0x28000, -0x20000, 3, 0, 0x28000, -0x20000 });
	TABLE(int32 debrisInfo2[13], { 3, 4, 0, 0, -0x20000, 5, 0, -0x28000, -0x20000, 5, 1, 0x28000, -0x20000 });
	int32 boundsL;
	int32 boundsR;
	int32 boundsM;
	int32 boundsT;
	int32 boundsB;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxGather;
	uint16 sfxBounce;
	uint16 sfxRelease;
	uint16 aniFrames;
	uint16 waterFrames;
};

struct EntityAmoebaDroid {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 type;
	int32 timer;
	int32 invincibleTimer;
	int32 health;
	int32 blobAngleX;
	int32 blobAngleY;
	int32 blobAmplitude;
	int32 blobRadius;
	Vector2 offsetPos;
	Entity* blobs[AMOEBADROID_BLOB_COUNT];
	Entity* parent;
	Animator animator;
	Animator attractorTopAnimator;
	Animator attractorSideAnimator;
	Hitbox hitbox;
};
