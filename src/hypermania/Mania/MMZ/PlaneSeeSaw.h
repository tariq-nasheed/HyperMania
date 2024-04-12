#pragma once

struct ObjectPlaneSeeSaw {
	RSDK_OBJECT
	uint16 aniFrames;
	uint16 sfxSpring;
	uint16 sfxFlipper;
};

struct EntityPlaneSeeSaw {
	RSDK_ENTITY
	StateMachine(state);
	int32 unused;
	int32 seeSawPos;
	Animator platformAnimator;
	Animator swingAnimator;
	Animator weightAnimator;
};