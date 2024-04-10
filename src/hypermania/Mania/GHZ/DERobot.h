#ifndef OBJ_DEROBOT_H
#define OBJ_DEROBOT_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
	Hitbox hitboxHand;
	Hitbox hitboxBody;
	uint16 unused1;
	uint16 unused2;
	uint16 unused3;
	uint16 unused4;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxTargeting;
	uint16 sfxImpact;
	uint16 sfxLedgeBreak;
	uint16 sfxBuzzsaw;
	uint16 sfxDrop;
	uint16 sfxButton2;
	uint16 sfxHullClose;
} ObjectDERobot;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 unused1;
	int32 unused2;
	int32 unused3;
	int32 unused4;
	Entity* parent;
	Entity* head;
	Entity* shoulderFront;
	Entity* eggman;
	Entity* legs[6];
	Entity* arms[4];
	int32 movingSide;
	int32 unused5;
	int32 angleVel;
	int32 angleInc;
	Vector2 offset;
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 armExtend;
	int32 destroyedTerrainX;
	int32 kneeAngleVel;
	int32 angleVelStart;
	int32 angleMaxInc;
	Hitbox hitbox;
	Animator mainAnimator;
	Animator altAnimator;
	Animator armAnimator;
	int32 aniID;
	int32 frameID;
} EntityDERobot;

extern ObjectDERobot* DERobot;

extern void (*DERobot_State_FallLand)();
extern void (*DERobot_State_Walk)();
extern void (*DERobot_State_ArmAttack)();
extern void (*DERobot_Hit)();

void DERobot_EnemyInfoHook();

#define OBJ_DEROBOT_SETUP \
  IMPORT_PUBLIC_FUNC(DERobot_State_FallLand); \
  IMPORT_PUBLIC_FUNC(DERobot_State_Walk); \
  IMPORT_PUBLIC_FUNC(DERobot_State_ArmAttack); \
  IMPORT_PUBLIC_FUNC(DERobot_Hit); \
  REGISTER_ENEMY(DERobot)

#endif //! OBJ_DEROBOT_H
