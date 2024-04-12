#pragma once

struct ObjectJawz {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	uint16 aniFrames;
};

struct EntityJawz {
	RSDK_ENTITY
	uint8 triggerDir;
	StateMachine(state);
	Vector2 startPos;
	Animator animator;
};
