#pragma once

typedef enum {
	DRILLERDROIDO_MAIN,
	DRILLERDROIDO_FIREBALLEMITTER,
	DRILLERDROIDO_TARGET,
	DRILLERDROIDO_UNUSED1,
	DRILLERDROIDO_UNUSED2,
} DrillerdroidOTypes;

struct ObjectDrillerdroidO {
	RSDK_OBJECT
	Hitbox hitboxCore;
	Hitbox hitboxPistonL;
	Hitbox hitboxPistonR;
	Hitbox hitboxDrillL;
	Hitbox hitboxDrillR;
	Hitbox hitboxLandPosSegmentBreak;
	Hitbox hitboxLandPosR;
	Hitbox hitboxLandPosL;
	Hitbox hitboxEmitterRange;
	int32 pistonPos[2];
	int32 drillPos[2];
	int32 pistonDelay[2];
	int32 drillDelay[2];
	int32 pistonMoveDir[2];
	int32 drillMoveDir[2];
	uint8 drillSfxTimer;
	bool32 playingDrillSfx;
	uint8 canBreakSegment;
	int32 childSlotStart;
	uint8 currentLevel;
	bool32 emitFireballs;
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
};

// Entity Class
struct EntityDrillerdroidO {
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
