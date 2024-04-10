#ifndef OBJ_METERDROID_H
#define OBJ_METERDROID_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	TABLE(int32 debrisSpeeds[21],
	      { 5, 0, 0, -0x20000, -0x28000, 1, 0, 0x20000, -0x20000, 2, 0, -0x28000, -0x10000, 3, 0, 0x28000, -0x10000, 4, 0, 0x10000, 0x10000 });
	Hitbox hitboxBoss;
	Hitbox hitboxPropellor;
	Hitbox hitboxWrench;
	int32 boundsL;
	int32 boundsR;
	int32 boundsM;
	int32 boundsT;
	int32 boundsB;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxDestroy;
	uint16 sfxToss;
	uint16 sfxGrab;
	uint16 sfxValve;
	uint16 sfxWrench;
	uint16 aniFrames;
} ObjectMeterDroid;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 bgFadeAmount;
	Vector2 origin;
	Vector2 targetPos;
	Vector2 moveVel;
	Vector2 wrenchPos;
	Vector2 wrenchMoveVel;
	Vector2 wrenchMoveInc;
	int32 moveRadius;
	Entity* targetValve;
	Animator mainAnimator;
	Animator propellorAnimator;
	Animator armAnimator;
	Animator wrenchAnimator;
} EntityMeterDroid;

extern ObjectMeterDroid* MeterDroid;

extern void (*MeterDroid_State_TurningValve)();
extern void (*MeterDroid_State_StopTurningValve)();
extern void (*MeterDroid_State_WatchPlatformsPopUp)();
extern void (*MeterDroid_State_Destroyed)();
extern void (*MeterDroid_State_FinishAct)();
extern void (*MeterDroid_Hit)();

void MeterDroid_EnemyInfoHook();

#define OBJ_METERDROID_SETUP \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_TurningValve); \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_StopTurningValve); \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_WatchPlatformsPopUp); \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_Destroyed); \
  IMPORT_PUBLIC_FUNC(MeterDroid_State_FinishAct); \
  IMPORT_PUBLIC_FUNC(MeterDroid_Hit); \
  REGISTER_ENEMY(MeterDroid)

#endif //! OBJ_METERDROID_H
