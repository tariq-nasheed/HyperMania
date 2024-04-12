#pragma once

struct ObjectRollerMKII {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxObject;
	Hitbox hitboxInner_Rolling;
	Hitbox hitboxOuter_Rolling;
	Hitbox hitboxInner_Idle;
	Hitbox hitboxOuter_Idle;
	uint16 aniFrames;
	uint16 sfxBumper;
	uint16 sfxJump;
	uint16 sfxDropDash;
	uint16 sfxRelease;
	uint16 sfxSkidding;
};

struct EntityRollerMKII {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	uint8 timer;
	bool32 touchedGround;
	EntityPlayer* playerPtr;
	Animator animator;
};
