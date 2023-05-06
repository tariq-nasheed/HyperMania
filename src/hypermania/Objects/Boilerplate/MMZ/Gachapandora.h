#ifndef OBJ_GACHAPANDORA_H
#define OBJ_GACHAPANDORA_H

#include "GameAPI/Game.h"

#define GACHAPANDORA_CAPSULE_COUNT (4)

typedef enum {
	GACHAPANDORA_MAIN,
	GACHAPANDORA_EGGMAN,
	GACHAPANDORA_PRIZE,
	GACHAPANDORA_AMY,
	GACHAPANDORA_DRILLER,
	GACHAPANDORA_FIREDROPPER,
	GACHAPANDORA_FIREBALL,
	GACHAPANDORA_DEBRIS,
	GACHAPANDORA_SPARK,
} GachapandoraTypes;

typedef struct {
	RSDK_OBJECT
	TABLE(int32 capsuleOffsets[56],
	      { 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 49, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53,
	        54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 53, 53, 53, 52, 52, 52, 52, 51, 51, 51, 50, 50, 50, 50, 49, 49, 48, 48 });
	uint8 destroyedToys;
	uint8 handleDir;
	uint8 eggmanDir;
	uint8 capsuleOffsetL[4];
	uint8 capsuleSpeedL[4];
	uint8 capsuleMaxL[4];
	uint8 capsuleTypeL[4];
	uint8 capsuleDelayL[4];
	uint8 capsuleOffsetR[4];
	uint8 capsuleSpeedR[4];
	uint8 capsuleMaxR[4];
	uint8 capsuleTypeR[4];
	uint8 capsuleDelayR[4];
	int16 handleSpinTimer;
	uint8 nextPrizeType;
	int8 nextCapsuleL;
	int8 nextCapsuleR;
	int8 lastCapsuleType;
	uint8 capsuleCount[3];
	uint8 capsuleSide;
	uint8 debrisTimer;
	uint8 sideSparkTimer[2];
	int32 unused1;
	int32 unused2;
	uint8 activeToys;
	uint8 awardAchievement;
	Entity* eggman;
	uint16 aniFrames;
	uint16 eggmanFrames;
	Hitbox hitboxHandle;
	Hitbox hitboxAmyRange;
	Hitbox hitboxAmy;
	Hitbox hitboxFireball;
	Hitbox hitboxDrill;
	Hitbox hitboxSpark;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxUnravel;
	uint16 sfxPon;
	uint16 sfxFireball;
	uint16 sfxGiggle;
} ObjectGachapandora;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 unused;
	uint8 type;
	uint16 shakeTimer;
	uint16 shakeCount;
	uint16 prevShakeFlags;
	int32 timer;
	int32 startY;
	int32 invincibilityTimer;
	uint8 health;
	Vector2 originPos;
	Entity* parent;
	Animator mainAnimator;
	Animator eggmanAnimator;
	Animator handleAnimator;
	Animator capsuleAnimator;
	Hitbox hitbox;
} EntityGachapandora;

extern ObjectGachapandora* Gachapandora;

extern void (*Gachapandora_StatePrize_DrillerMove)();
extern void (*Gachapandora_StatePrize_FireDropperMove)();
extern void (*Gachapandora_StatePrize_AmyWalk)();
extern void (*Gachapandora_StatePrize_AmyIdle)();
extern void (*Gachapandora_StatePrize_Destroyed)();

void Gachapandora_EnemyInfoHook();

#define OBJ_GACHAPANDORA_SETUP \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_DrillerMove); \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_FireDropperMove); \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_AmyWalk); \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_AmyIdle); \
  IMPORT_PUBLIC_FUNC(Gachapandora_StatePrize_Destroyed); \
  REGISTER_ENEMY(Gachapandora)

#endif //! OBJ_GACHAPANDORA_H
