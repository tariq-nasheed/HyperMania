#pragma once

typedef enum {
	EGGPISTON_PISTON,
	EGGPISTON_CONTROL,
	EGGPISTON_EMITTER,
	EGGPISTON_BARRIER,
	EGGPISTON_PLASMABALL,
	EGGPISTON_ALARM,
} EggPistonMKIITypes;

struct ObjectEggPistonsMKII {
	RSDK_OBJECT
	int32 invincibilityTimer;
	int32 health;
	int32 alarmAngle;
	int32 alarmTimer;
	Entity* controller;
	Entity* pistons[5];
	uint8 pistonCount;
	uint8 isPhase2;
	uint8 pistonID;
	uint16 aniFrames;
	uint16 eggmanFrames;
	uint16 sfxHit;
	uint16 sfxWall;
	uint16 sfxElectrify;
	uint16 sfxExplosion;
	uint16 sfxAlarm;
};

struct EntityEggPistonsMKII {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	uint8 type;
	int32 timer;
	int32 pistonID;
	Entity* parent;
	Animator mainAnimator;
	Animator altAnimator;
	Hitbox hitbox;
};
