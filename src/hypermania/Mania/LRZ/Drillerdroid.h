#pragma once

typedef enum {
	DRILLERDROID_MAIN,
	DRILLERDROID_TARGET,
	DRILLERDROID_UNUSED,
} DrillerdroidTypes;

struct ObjectDrillerdroid {
	RSDK_OBJECT
	Hitbox hitboxCore;
	Hitbox hitboxPistonL;
	Hitbox hitboxPistonR;
	Hitbox hitboxDrillL;
	Hitbox hitboxDrillR;
	int32 pistonPos[2];
	int32 drillPos[2];
	int32 pistonDelay[2];
	int32 drillDelay[2];
	int32 pistonMoveDir[2];
	int32 drillMoveDir[2];
	uint8 platformActive[5];
	uint8 arenaSegment;
	uint8 playerTimers[PLAYER_COUNT];
	uint8 drillSfxTimer;
	bool32 playingDrillSfx;
	uint8 armorHealth;
	uint8 jumpsRemaining;
	uint8 canBreakSegment;
	int32 stalatiteOffset;
	Entity* boss;
	uint16 aniFrames;
	uint16 ticFrames;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxDrill;
	uint16 sfxImpact;
	uint16 sfxJump;
	uint16 sfxTargeting;
	uint16 sfxSizzle;
	uint16 sfxDrop;
	uint16 sfxFail;
	uint16 sfxClang;
};

struct EntityDrillerdroid {
	RSDK_ENTITY
	uint8 type;
	StateMachine(state);
	StateMachine(stateDraw);
	Animator mainAnimator;
	Animator armorAnimator;
	Animator targetLockAnimator;
	EntityPlayer* target;
	Vector2 targetEdgeOffset;
	int32 startY;
	int32 timer;
	uint8 invincibilityTimer;
	int8 health;
};
