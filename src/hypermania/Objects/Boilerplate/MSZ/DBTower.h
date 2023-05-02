#ifndef OBJ_DBTOWER_H
#define OBJ_DBTOWER_H

#include "GameAPI/Game.h"

#define DBTOWER_SEGMENT_COUNT (4)

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxSegment;
	bool32 defeated;
	uint16 sfxRocketJet;
	uint16 sfxHit;
	uint16 sfxExplosion2;
	uint16 sfxExplosion3;
	uint16 sfxBumper3;
	uint16 sfxAssemble;
	uint16 sfxRocketJet2;
	uint16 sfxRockemSockem;
	uint16 aniFrames;
} ObjectDBTower;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	Vector2 originPos;
	Vector2 bodyPositions[DBTOWER_SEGMENT_COUNT];
	int32 segmentUnused1[DBTOWER_SEGMENT_COUNT];
	int32 segmentUnused2[DBTOWER_SEGMENT_COUNT];
	int32 segmentUnused3[DBTOWER_SEGMENT_COUNT];
	int32 bodyAngles[DBTOWER_SEGMENT_COUNT];
	int32 wobbleAngle;
	int32 wobbleAngleVel;
	int32 segmentOffsetY;
	int32 xOffsetAngle;
	uint8 connectedSegmentCount;
	Animator* segmentAnimators[DBTOWER_SEGMENT_COUNT];
	uint8 playerTimers[PLAYER_COUNT];
	Animator headAnimator;
	Animator bodyAnimator;
} EntityDBTower;

extern ObjectDBTower* DBTower;

extern void (*DBTower_State_HandleBoss)();
extern void (*DBTower_State_Destroyed)();

void DBTower_EnemyInfoHook();

#define OBJ_DBTOWER_SETUP \
  IMPORT_PUBLIC_FUNC(DBTower_State_HandleBoss); \
  IMPORT_PUBLIC_FUNC(DBTower_State_Destroyed); \
  REGISTER_ENEMY(DBTower)

#endif //! OBJ_DBTOWER_H
