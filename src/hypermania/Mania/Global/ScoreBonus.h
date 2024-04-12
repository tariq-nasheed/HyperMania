#pragma once

struct ObjectScoreBonus {
	RSDK_OBJECT
	uint16 aniFrames;
};

struct EntityScoreBonus {
	RSDK_ENTITY
	int32 timer;
	Animator animator;
};
