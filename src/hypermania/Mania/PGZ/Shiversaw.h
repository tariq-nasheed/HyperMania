#ifndef OBJ_SHIVERSAW_H
#define OBJ_SHIVERSAW_H

#include "GameAPI/Game.h"

#define SHIVERSAW_SAW_COUNT (2)

typedef struct {
	RSDK_OBJECT
	uint8 health;
	uint8 invincibilityTimer;
	int32 timer;
	uint16 aniFrames;
	Hitbox hitboxBoss;
	Hitbox hitboxSaw;
	Hitbox hitboxR;
	Hitbox hitboxB;
	Hitbox hitboxT;
	Hitbox hitboxL;
#if MANIA_USE_PLUS
	Hitbox hitboxEntryTrigger;
	Hitbox hitboxEntryBounds;
#endif
	uint16 sfxHit;
	uint16 sfxExplosion2;
	uint16 sfxTargeting;
	uint16 sfxRocketJet;
	uint16 sfxExplosion3;
} ObjectShiversaw;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateSaw[SHIVERSAW_SAW_COUNT]);
	uint8 sawID;
	int32 timer;
	int32 sawTimers[SHIVERSAW_SAW_COUNT];
	int32 sawRadiusVel[SHIVERSAW_SAW_COUNT];
	int32 unused1;
	int32 unused2;
	int32 startY;
	Vector2 origin;
	int32 sawRadius[SHIVERSAW_SAW_COUNT];
	int32 sawAngles[SHIVERSAW_SAW_COUNT];
	int32 sawTargetAngles[SHIVERSAW_SAW_COUNT];
	Vector2 sawPos[SHIVERSAW_SAW_COUNT];
	int32 storedVelX;
	int32 circleRadius;
	Animator tanksAnimator;
	Animator bellowsAnimator;
	Animator connectorAnimator;
	Animator armAnimator;
	Animator spinnerAnimator;
	Animator sawAnimator[SHIVERSAW_SAW_COUNT];
} EntityShiversaw;

extern ObjectShiversaw* Shiversaw;

extern void (*Shiversaw_State_Idle)();
extern void (*Shiversaw_State_MoveToPlayer)();
extern void (*Shiversaw_State_HitRecoil)();
extern void (*Shiversaw_Hit)();

void Shiversaw_EnemyInfoHook();

#define OBJ_SHIVERSAW_SETUP \
  IMPORT_PUBLIC_FUNC(Shiversaw_State_Idle); \
  IMPORT_PUBLIC_FUNC(Shiversaw_State_MoveToPlayer); \
  IMPORT_PUBLIC_FUNC(Shiversaw_State_HitRecoil); \
  IMPORT_PUBLIC_FUNC(Shiversaw_Hit); \
  REGISTER_ENEMY(Shiversaw)

#endif //! OBJ_SHIVERSAW_H