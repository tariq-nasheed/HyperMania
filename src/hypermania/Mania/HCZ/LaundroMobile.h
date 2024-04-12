#pragma once

struct ObjectWhirlpool {
	RSDK_OBJECT
	uint16 aniFrames;
	uint16 sfxWhirlpool;
	bool32 playingWhirlpoolSfx;
	int32 sfxChannel;
	int32 timer;
};

struct EntityWhirlpool {
	RSDK_ENTITY
	int32 angVel;
	int32 yVel;
	Vector2 size;
	uint8 activePlayers;
	Vector2 startPos;
	int32 unused;
	int32 bubbleAngles[128];
	int32 playerAngle[PLAYER_COUNT];
	int32 playerAmplitude[PLAYER_COUNT];
	Hitbox hitbox;
	Animator animator;
};

typedef enum {
	LAUNDROMOBILE_BOSS,
	LAUNDROMOBILE_BOMB,
	LAUNDROMOBILE_LAUNDRY,
	LAUNDROMOBILE_LOOPPOINT,
	LAUNDROMOBILE_BLOCK,
	LAUNDROMOBILE_SPIKES,
	LAUNDROMOBILE_DELAYEDSPLASH,
} LaundroMobileTypes;

struct ObjectLaundroMobile {
	RSDK_OBJECT
	uint8 health;
	uint8 invincibilityTimer;
	int32 currentVelocity;
	Entity* loopPoints[6];
	uint8 nextLoopPoint;
	uint8 playingLoopSfx;
	uint8 loopSfxTimer;
	uint8 attackDir;
	int8 attackCount;
	TABLE(int32 attackCounts[8], { 1, 2, 2, 2, 1, 2, 2, 3 });
	uint8 isUnderwater;
	int32 animSpeed;
	uint8 rocketActive;
	int32 rocketAngles[4];
	Vector2 rocketPositions[4];
	uint8 unused[4];
	int32 rocketSpeeds[2];
	int32 playerRadius[PLAYER_COUNT];
	int32 playerAngles[PLAYER_COUNT];
	uint8 travelledPaths;
	uint8 useStageWrap;
	Entity* laundroMobile;
	TABLE(int32 debrisInfo[73], { 12,       6,        0, -0x50000, -0x40000, 0, 0,        7,        0, 0x50000,  -0x40000, 0, 0,        10,       0,
	                              -0x50000, -0x40000, 0, 0,        11,       0, 0x50000,  -0x40000, 0, 0,        10,       0, -0x50000, -0x40000, 0,
	                              0x200000, 11,       0, 0x50000,  -0x40000, 0, 0x200000, 10,       0, -0x50000, -0x40000, 0, 0x400000, 11,       0,
	                              0x50000,  -0x40000, 0, 0x400000, 8,        0, -0x50000, -0x40000, 0, 0x400000, 9,        0, 0x50000,  -0x40000, 0,
	                              0x400000, 12,       0, -0x50000, -0x40000, 0, 0x400000, 13,       0, 0x50000,  -0x40000, 0, 0x400000 });
	uint16 aniFrames;
	uint16 eggmanFrames;
	Hitbox hitboxBoss;
	Hitbox hitboxMissile;
	Hitbox hitboxBox;
	Hitbox hitboxBomb;
	Hitbox innerBox;
	Hitbox outerBox;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxButton2;
	uint16 sfxFan;
	uint16 sfxRoll;
	uint16 sfxWash;
	uint16 sfxHullClose;
	uint16 sfxPush;
	uint16 sfxFireball;
	uint16 sfxButton;
	uint16 sfxLedgeBreak;
	uint16 sfxPimPom;
#if MANIA_USE_PLUS
	uint16 sfxRumble;
	uint16 sfxImpact;
#endif
};

struct EntityLaundroMobile {
	RSDK_ENTITY
	uint8 type;
	StateMachine(state);
	StateMachine(stateDraw);
	int32 timer;
	int32 startY;
	Vector2 originPos;
	Vector2 unusedPos;
	EntityWhirlpool* whirlpool;
	Animator mainAnimator;
	Animator propellerAnimator;
	Animator eggmanAnimator;
	Animator flameAnimator;
};
