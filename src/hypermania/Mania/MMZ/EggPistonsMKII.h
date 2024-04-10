#ifndef OBJ_EGGPISTONSMKII_H
#define OBJ_EGGPISTONSMKII_H

#include "GameAPI/Game.h"

typedef enum {
	EGGPISTON_PISTON,
	EGGPISTON_CONTROL,
	EGGPISTON_EMITTER,
	EGGPISTON_BARRIER,
	EGGPISTON_PLASMABALL,
	EGGPISTON_ALARM,
} EggPistonMKIITypes;

typedef struct {
	RSDK_OBJECT
	int32 invincibilityTimer;
	int32 health;
	int32 alarmAngle;
	int32 alarmTimer;
	Entity* controller;
	Entity* pistons[5];
	uint8 pistonCount;
	uint8 isPhase2;
	uint8 pistonID;
	uint16 aniFrames;
	uint16 eggmanFrames;
	uint16 sfxHit;
	uint16 sfxWall;
	uint16 sfxElectrify;
	uint16 sfxExplosion;
	uint16 sfxAlarm;
} ObjectEggPistonsMKII;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	uint8 type;
	int32 timer;
	int32 pistonID;
	Entity* parent;
	Animator mainAnimator;
	Animator altAnimator;
	Hitbox hitbox;
} EntityEggPistonsMKII;

extern ObjectEggPistonsMKII* EggPistonsMKII;

extern void (*EggPistonsMKII_State_ClassicMode)();
extern void (*EggPistonsMKII_State_PinchMode)();
extern void (*EggPistonsMKII_State_Destroyed)();
extern void (*EggPistonsMKII_Hit)();

void EggPistonsMKII_EnemyInfoHook();

#define OBJ_EGGPISTONSMKII_SETUP \
  IMPORT_PUBLIC_FUNC(EggPistonsMKII_State_ClassicMode); \
  IMPORT_PUBLIC_FUNC(EggPistonsMKII_State_PinchMode); \
  IMPORT_PUBLIC_FUNC(EggPistonsMKII_State_Destroyed); \
  IMPORT_PUBLIC_FUNC(EggPistonsMKII_Hit); \
  REGISTER_ENEMY(EggPistonsMKII)

#endif //! OBJ_EGGPISTONSMKII_H
