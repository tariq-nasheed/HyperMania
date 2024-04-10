#ifndef OBJ_SENTRYBUG_H
#define OBJ_SENTRYBUG_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	TABLE(int32 orbOffsets_Attatched[84], { -0x50000, 0x30000,  -0x90000, 0xA0000,  -0x70000, 0x100000, 0x70000,  0x30000,  0x30000,  0xA0000,
	                                        -0x30000, 0x100000, -0x70000, 0x30000,  -0xB0000, 0xA0000,  -0x80000, 0x100000, 0x90000,  0x30000,
	                                        0x60000,  0xA0000,  0,        0x100000, -0x90000, 0x30000,  -0xB0000, 0xA0000,  -0x80000, 0x100000,
	                                        0x90000,  0x30000,  0x80000,  0xA0000,  0x30000,  0x100000, -0x90000, 0x30000,  -0xB0000, 0xA0000,
	                                        -0x80000, 0x100000, 0x90000,  0x30000,  0xB0000,  0xA0000,  0x80000,  0x100000, 0x90000,  0x30000,
	                                        0xB0000,  0xA0000,  0x80000,  0x100000, -0x90000, 0x30000,  -0x80000, 0xA0000,  -0x30000, 0x100000,
	                                        0x70000,  0x30000,  0xB0000,  0xA0000,  0x80000,  0x100000, -0x90000, 0x30000,  -0x60000, 0xA0000,
	                                        0,        0x100000, 0x50000,  0x30000,  0x90000,  0xA0000,  0x70000,  0x100000, -0x70000, 0x30000,
	                                        -0x30000, 0xA0000,  0x30000,  0x100000 });
	TABLE(int32 dropVelR[12], { -0x10000, -0x10000, -0x20000, -0x8000, -0x10000, 0x8000, 0x10000, -0x10000, 0x20000, -0x8000, 0x10000, 0x8000 });
	TABLE(int32 dropVelL[12], { 0x10000, -0x10000, 0x20000, -0x8000, 0x10000, 0x8000, -0x10000, -0x10000, -0x20000, -0x8000, -0x10000, 0x8000 });
	Hitbox hitbox;
	uint16 meshFrames;
	uint16 sceneIndex;
	uint16 aniFrames;
	uint16 sfxPon;
	uint16 sfxSwarm;
} ObjectSentryBug;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateOrbs);
	uint8 speed;
	Vector2 amplitude;
	bool32 orbsDetatched;
	bool32 showNet;
	int32 timer;
	Vector2 originPos;
	Vector2 startPos;
	EntityPlayer* playerPtr;
	Vector2 netPos;
	int32 netRotation;
	int32 netScale;
	int32 netColor;
	Vector2 orbPositions[6];
	Vector2 orbVelocities[6];
	Animator unusedAnimator;
	Matrix matUnused;
	Matrix matTransform;
	Matrix matWorld;
	Animator bugAnimator;
	Animator orbAnimator;
} EntitySentryBug;

extern ObjectSentryBug* SentryBug;

extern void (*SentryBug_State_AwaitPlayer)();
extern void (*SentryBug_State_DropOrbs)();
extern void (*SentryBug_State_NetAppear)();
extern void (*SentryBug_State_NetShrink)();
extern void (*SentryBug_State_NetFlash)();
extern void (*SentryBug_State_ReturnToSlots)();

void SentryBug_EnemyInfoHook();

#define OBJ_SENTRYBUG_SETUP \
  IMPORT_PUBLIC_FUNC(SentryBug_State_AwaitPlayer); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_DropOrbs); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_NetAppear); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_NetShrink); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_NetFlash); \
  IMPORT_PUBLIC_FUNC(SentryBug_State_ReturnToSlots); \
  REGISTER_ENEMY(SentryBug)

#endif //! OBJ_SENTRYBUG_H
