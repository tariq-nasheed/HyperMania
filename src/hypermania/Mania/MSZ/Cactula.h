#pragma once

struct ObjectCactula {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
	uint16 sfxCactDrop;
};

struct EntityCactula {
	RSDK_ENTITY
	StateMachine(state);
	int32 unused;
	int32 offsetY;
	bool32 droppedBomb;
	Animator bodyTopAnimator;
	Animator bodyBottomAnimator;
	Animator propellerAnimator;
};
