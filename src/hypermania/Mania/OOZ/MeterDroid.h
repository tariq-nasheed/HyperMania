#pragma once

struct ObjectMeterDroid {
	RSDK_OBJECT
	TABLE(int32 debrisSpeeds[21],
	      { 5, 0, 0, -0x20000, -0x28000, 1, 0, 0x20000, -0x20000, 2, 0, -0x28000, -0x10000, 3, 0, 0x28000, -0x10000, 4, 0, 0x10000, 0x10000 });
	Hitbox hitboxBoss;
	Hitbox hitboxPropellor;
	Hitbox hitboxWrench;
	int32 boundsL;
	int32 boundsR;
	int32 boundsM;
	int32 boundsT;
	int32 boundsB;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxDestroy;
	uint16 sfxToss;
	uint16 sfxGrab;
	uint16 sfxValve;
	uint16 sfxWrench;
	uint16 aniFrames;
};

struct EntityMeterDroid {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 bgFadeAmount;
	Vector2 origin;
	Vector2 targetPos;
	Vector2 moveVel;
	Vector2 wrenchPos;
	Vector2 wrenchMoveVel;
	Vector2 wrenchMoveInc;
	int32 moveRadius;
	Entity* targetValve;
	Animator mainAnimator;
	Animator propellorAnimator;
	Animator armAnimator;
	Animator wrenchAnimator;
};
