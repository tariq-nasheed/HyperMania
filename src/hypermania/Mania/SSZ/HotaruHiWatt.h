#pragma once

typedef enum {
	HHW_BOSS,
	HHW_SINGLE_HOTARU,
	HHW_PAIR_HOTARU,
	HHW_UNUSED1,
	HHW_SMALL_HOTARU,
	HHW_FLASH,
	HHW_UNUSED2,
	HHW_MINILASER,
	HHW_ELECTRICORB,
} HHWTypes;

struct ObjectHotaruHiWatt {
	RSDK_OBJECT
	TABLE(int32 debrisInfo[33],
	      { 8, 0, 0,        -0x20000, -0x28000, 1, 0,       0x20000,  -0x28000, 2, 0,        -0x28000, -0x20000, 3, 0,       0x28000, -0x20000,
	        4, 0, -0x28000, -0x18000, 5,        0, 0x28000, -0x18000, 6,        0, -0x20000, -0x10000, 7,        0, 0x20000, -0x10000 });
	int32 boundsL;
	int32 boundsM;
	int32 boundsR;
	int32 boundsT;
	int32 boundsB;
	int32 startY;
	bool32 spawnedLaserStrike;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxHHWAppear;
	uint16 sfxFlash;
	uint16 sfxLaser;
	uint16 sfxAppear;
	uint16 sfxFly;
	uint16 sfxFlyUp;
	uint16 sfxCharge;
	uint16 aniFrames;
	uint16 hotaruFrames;
};

struct EntityHotaruHiWatt {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(nextState);
	StateMachine(stateDraw);
	int32 type;
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 formationCircleRadius;
	int32 bulbAlpha;
	int32 unused;
	Vector2 originPos;
	Vector2 targetPos;
	Vector2 laserImpactPos;
	Entity* parents[3];
	bool32 playingBossTrack;
	Animator mainAnimator;
	Animator headAnimator;
	Animator bulbAnimator;
	Animator bulbFlashAnimator;
	Animator laserImpactAnimator;
	Hitbox hitbox;
};
