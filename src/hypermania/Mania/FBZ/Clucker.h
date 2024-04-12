#pragma once

struct ObjectClucker {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxSolid;
	Hitbox hitboxEgg;
	uint16 aniFrames;
	uint16 sfxShot;
};

struct EntityClucker {
	RSDK_ENTITY
	StateMachine(state);
	int32 yOffset;
	int32 xOffset;
	uint8 timer;
	uint16 delay;
	bool32 hasParent;
	Animator animator;
};
