#ifndef MANIA_ITEMBOX_H
#define MANIA_ITEMBOX_H

typedef enum {
	ITEMBOX_RING,
	ITEMBOX_BLUESHIELD,
	ITEMBOX_BUBBLESHIELD,
	ITEMBOX_FIRESHIELD,
	ITEMBOX_LIGHTNINGSHIELD,
	ITEMBOX_INVINCIBLE,
	ITEMBOX_SNEAKERS,
	ITEMBOX_1UP_SONIC,
	ITEMBOX_1UP_TAILS,
	ITEMBOX_1UP_KNUX,
	ITEMBOX_EGGMAN,
	ITEMBOX_HYPERRING,
	ITEMBOX_SWAP,
	ITEMBOX_RANDOM,
	ITEMBOX_SUPER,
#if MANIA_USE_PLUS
	ITEMBOX_1UP_MIGHTY,
	ITEMBOX_1UP_RAY,
	ITEMBOX_STOCK,
#endif
	ITEMBOX_COUNT
} ItemBoxTypes;

// Object Class
typedef struct {
	RSDK_OBJECT
	Hitbox hitboxItemBox;
	Hitbox hitboxHidden;
	int32 brokenFrame;
	uint16 aniFrames;
	uint16 sfxDestroy;
	uint16 sfxTeleport;
	uint16 sfxHyperRing;
#if MANIA_USE_PLUS
	uint16 sfxPowerDown;
	uint16 sfxRecovery;
#endif
} ObjectItemBox;

// Entity Class
typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	ItemBoxTypes type;
	Vector2 contentsPos;
	Vector2 moveOffset;
	int32 contentsSpeed;
	Entity *storedEntity;
	int32 timer;
	bool32 isFalling;
	bool32 isContents;
	bool32 hidden;
	ManiaPlaneFilterTypes planeFilter;
	bool32 lrzConvPhys;
	Animator boxAnimator;
	Animator contentsAnimator;
	Animator overlayAnimator;
	Animator debrisAnimator;
#if MANIA_USE_PLUS
	Entity *parent;
#endif
} EntityItemBox;

#endif //! MANIA_ITEMBOX_H