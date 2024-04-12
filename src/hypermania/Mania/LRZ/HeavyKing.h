#pragma once

struct ObjectHeavyKing {
	RSDK_OBJECT
	TABLE(int32 attackPattern[32], { 0, 0, 1, 0, 2, 2, 1, 0, 0, 1, 1, 2, 0, 2, 0, 0, 2, 1, 1, 2, 1, 0, 1, 0, 2, 2, 0, 1, 0, 0, 2, 1 });
	int32 attackPatternPos;
	Hitbox hitboxBody;
	Hitbox hitboxBoss;
	Hitbox hitboxCharging;
	int32 boundsL;
	int32 boundsM;
	int32 boundsR;
	int32 spinRaySpawnPos;
	int32 startY;
	uint16 sfxHit;
	uint16 sfxImpact2;
	uint16 sfxImpact5;
	uint16 sfxCharge;
	uint16 sfxExplosion;
	uint16 sfxFreeze;
	uint16 sfxRodPlant;
	uint16 sfxRodShine;
	uint16 sfxElecOn;
	uint16 sfxTwinCharge;
	uint16 sfxImpact6;
	uint16 aniFrames;
	uint16 cutsceneFrames;
};

struct EntityHeavyKing {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateStore);
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 curAttack;
	int32 attacksRemaining;
	Vector2 originPos;
	Entity* claw;
	Entity* masterEmerald;
	Entity* targetEmerald;
	Animator bodyAnimator;
	Animator scepterAnimator;
	Animator electricityAnimator;
	Animator storedBodyAnimator;
	Animator storedScepterAnimator;
};
