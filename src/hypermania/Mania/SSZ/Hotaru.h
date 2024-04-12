#pragma once

typedef enum {
	HOTARU_ATTACK_IDLE,
	HOTARU_ATTACK_CHARGING,
	HOTARU_ATTACK_ATTACKING,
} HotaruAttackStates;

struct ObjectHotaru {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxTrigger;
	int32 unused1;
	int32 unused2;
	Hitbox hitboxElectricity;
	uint16 aniFrames;
};

struct EntityHotaru {
	RSDK_ENTITY
	StateMachine(state);
	uint8 quality;
	Vector2 dist;
	int32 distX1;
	int32 distX2;
	int32 speed;
	uint8 preset;
	Vector2 offset2;
	Vector2 offset1;
	uint8 hotaruDir;
	uint8 destroyedHotarus;
	Vector2 startPos;
	uint8 startDir;
	uint8 screenID;
	int32 timer;
	EntityPlayer* playerPtr;
	uint8 unused1;
	uint8 unused2;
	uint8 attackState;
	Vector2 electricityOffset;
	Animator mainAnimator;
	Animator bulbAnimator;
	Animator electricityAnimator;
};
