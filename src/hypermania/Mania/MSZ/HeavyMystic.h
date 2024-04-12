#pragma once

typedef enum {
	MYSTIC_MISCHIEF,
	MYSTIC_BOSS,
	MYSTIC_BOX,
	MYSTIC_CORK,
	MYSTIC_BOMB,
	MYSTIC_DEBRIS,
} HeavyMysticTypes;

struct ObjectHeavyMystic {
	RSDK_OBJECT
	int32 boundsL;
	int32 boundsR;
	int32 boundsM;
	int32 boundsT;
	int32 boundsB;
	int32 curtainLinePos;
	uint16 sfxAssemble;
	uint16 sfxMagicBox;
	uint16 sfxClack;
	uint16 sfxPowerDown;
	uint16 sfxImpact;
	uint16 sfxPon;
	uint16 sfxDrop;
	uint16 sfxImpact2;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxPoof;
	uint16 sfxTwinkle;
	uint16 sfxHat;
	uint16 sfxHatNode;
	uint16 sfxBleeps;
	uint16 sfxTransform;
	uint16 sfxAppear1;
	uint16 aniFrames;
	uint16 rouguesFrames;
};

struct EntityHeavyMystic {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 type;
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 rougeHealth;
	int32 particleFXTimer;
	int32 unused;
	int32 attackID;
	int32 rougeID;
	Vector2 targetPos;
	Animator animator;
	Hitbox hitbox;
};
