#pragma once

struct ObjectBubbler {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
};

struct EntityBubbler {
	RSDK_ENTITY
	StateMachine(state);
	int16 timer;
	uint16 spawnTimer;
	Vector2 startPos;
	uint8 startDir;
	Animator bodyHitbox;
	Animator flameAnimator;
};
