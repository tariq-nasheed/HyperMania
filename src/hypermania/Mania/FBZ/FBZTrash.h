#pragma once

typedef enum {
	FBZTRASH_TRASH,
	FBZTRASH_UNUSED,
	FBZTRASH_ORB,
	FBZTRASH_ORBINAUT,
} FBZTrashTypes;

struct ObjectFBZTrash {
	RSDK_OBJECT
	uint16 aniFrames;
};

struct EntityFBZTrash {
	RSDK_ENTITY
	StateMachine(state);
	FBZTrashTypes type;
	int32 frameID;
	int32 rumbleMove;
	int32 timer;
	int32 radius;
	Vector2 targetPos;
	Vector2 startPos;
	void* parent;
	Hitbox hitbox;
	Animator animator;
};
