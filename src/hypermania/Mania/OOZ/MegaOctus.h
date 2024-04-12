#pragma once

typedef enum {
	MEGAOCTUS_BODY,
	MEGAOCTUS_UNUSED1,
	MEGAOCTUS_HARPOON,
	MEGAOCTUS_CANNON,
	MEGAOCTUS_ORB,
	MEGAOCTUS_ARM,
	MEGAOCTUS_LASER,
	MEGAOCTUS_ORBSHOT,
	MEGAOCTUS_UNUSED8,
	MEGAOCTUS_LASERFIRE,
} MegaOctusTypes;

struct ObjectMegaOctus {
	RSDK_OBJECT
	Entity* bossEntity;
	Animator noseAnimator;
	Animator boltsAnimator;
	Animator eggmanAnimator;
	Animator hatchBaseAnimator;
	Animator hatchOpenAnimator;
	int32 eggmanOffset;
	int32 eggmanVelocity;
	bool32 spawnHarpoon;
	int32 turnPos;
	TABLE(int32 turnOffsets[11], { -0x200000, -0x180000, -0x100000, -0xC0000, -0x80000, 0, 0x80000, 0xC0000, 0x100000, 0x180000, 0x200000 });
	TABLE(int32 cannonHeights[4], { -0x780000, -0x800000, -0x700000, -0x510000 });
	int32 orbHealth[2];
	bool32 defeated;
	uint16 aniFrames;
	uint16 eggmanFrames;
	uint16 hatchFrames;
	Hitbox hitbox;
	uint16 sfxBossHit;
	uint16 sfxExplosion;
	uint16 sfxLaser;
	uint16 sfxBullet;
	uint16 sfxHarpoon;
	uint16 sfxSurface;
	uint16 sfxLaserSplash;
};

struct EntityMegaOctus {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	uint8 type;
	int32 timer;
	int32 orbMoveAngle;
	int32 targetPos;
	int32 lastAttackHeight;
	int32 shotCount;
	int32 invincibilityTimer;
	uint8 health;
	Vector2 origin;
	int32 orbID;
	Entity* parent;
#if MANIA_USE_PLUS
	int32 tilePlatY;
#endif
	Animator animator;
	Animator altAnimator;
	Hitbox hitbox;
};
