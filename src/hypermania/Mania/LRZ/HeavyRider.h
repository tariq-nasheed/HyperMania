#pragma once

typedef enum {
	HEAVYRIDER_RIDER,
	HEAVYRIDER_PLANESWITCH,
	HEAVYRIDER_FORCECHARGE_LEFT,
	HEAVYRIDER_FORCECHARGE_RIGHT,
	HEAVYRIDER_UNUSED1,
	HEAVYRIDER_UNUSED2,
	HEAVYRIDER_PUFF,
	HEAVYRIDER_FIREBALL,
	HEAVYRIDER_JIMMY,
} HeavyRiderTypes;

typedef enum {
	HEAVYRIDER_ATK_RIDING_SCREENBOUNDS,
	HEAVYRIDER_ATK_RIDING_ARENABOUNDS,
	HEAVYRIDER_ATK_RIDING_USETRIGGERS,
	HEAVYRIDER_ATK_PREPCHARGE,
	HEAVYRIDER_ATK_CHARGE,
} HeavyRiderAttackIDs;

typedef enum {
	HEAVYRIDER_SPIKEBALL_NONE,
	HEAVYRIDER_SPIKEBALL_SWINGING,
	HEAVYRIDER_SPIKEBALL_UNUSED1,
	HEAVYRIDER_SPIKEBALL_UNUSED2,
	HEAVYRIDER_SPIKEBALL_UNUSED3,
	HEAVYRIDER_SPIKEBALL_UNUSED4,
	HEAVYRIDER_SPIKEBALL_UNUSED5,
	HEAVYRIDER_SPIKEBALL_THROWN,
} HeavyRiderSpikeBallStates;

typedef enum {
	HEAVYRIDER_WHEEL_NONE,
	HEAVYRIDER_WHEEL_EXTENDING,
	HEAVYRIDER_WHEEL_RETRACTING,
} HeavyRiderWheelStates;

struct ObjectHeavyRider {
	RSDK_OBJECT
	uint8 curAttack;
	uint8 spikeBallState;
	Vector2 spikeBallPos;
	uint8 spikeBallAngle;
	int32 wheelLength;
	uint8 wheelExtendState;
	uint8 health;
	uint8 invincibilityTimer;
	uint8 spawnDelay;
	uint8 playerTimers[PLAYER_COUNT];
	int32 spawnFireballs;
	int32 startY;
	uint8 chargeTimer;
#if MANIA_USE_PLUS
	Entity* outro;
#endif
	uint16 aniFrames;
	Hitbox hitboxRider;
	Hitbox hitboxSpikeBall;
	Hitbox innerBox;
	Hitbox outerBox;
	Hitbox hitboxRiderTrigger;
	Hitbox hitboxTrigger;
	Hitbox hitboxJimmy;
	Hitbox hitboxFireball;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxCharge;
	uint16 sfxLaunch;
	uint16 sfxSkid;
	uint16 sfxJump;
	uint16 sfxCheer;
	uint16 sfxBumper;
};

struct EntityHeavyRider {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	uint8 type;
	int32 flags;
	int32 size;
	bool32 affectPlayer;
	int32 timer;
	Animator mainAnimator;
	Animator thrustAnimator;
	Animator spikeBallAnimator;
	Animator fireballAnimator;
	Animator wheelieAnimator;
};
