#ifndef OBJ_GIGAMETAL_H
#define OBJ_GIGAMETAL_H

#include "GameAPI/Game.h"

#if MANIA_USE_PLUS

typedef enum {
	GIGAMETAL_HEAD,
	GIGAMETAL_SHOULDER,
	GIGAMETAL_BODY,
	GIGAMETAL_COVER,
	GIGAMETAL_EYE,
	GIGAMETAL_ARMFRONT,
	GIGAMETAL_ARMBACK,
	GIGAMETAL_LASERCHARGE,
	GIGAMETAL_LASEREDGE,
	GIGAMETAL_LASERBEAM,
	GIGAMETAL_SHARD,
} GigaMetalAniIDs;

typedef struct {
	RSDK_OBJECT
	int32 invincibleTimer;
	int32 explodeTimer;
	uint16 aniFrames;
	uint16 sfxRoar;
	uint16 sfxImpact;
	uint16 sfxTarget;
	uint16 sfxPimpom;
	uint16 sfxCannon;
	Hitbox hitboxLaser;
	Hitbox hitboxHand;
	Hitbox hitboxCore;
	Hitbox hitboxHead;
} ObjectGigaMetal;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	Entity* body;
	Entity* head;
	Entity* ruby;
	Entity* cover;
	Entity* shoulder;
	Entity* frontArm;
	Entity* backArm;
	Entity* metalSonic;
	int32 timer;
	int32 health;
	int32 attackTimer;
	Vector2 componentPos;
	Vector2 targetPos;
	Animator mainAnimator;
	Animator jointAnimator;
	Animator armAnimator;
	Animator handAnimator;
	uint8 aniID;
	uint8 frameID;
	int32 rotationAngles[3];
	int32 laserSize;
} EntityGigaMetal;

extern ObjectGigaMetal* GigaMetal;

extern void (*GigaMetal_StateBody_Marching)();
extern void (*GigaMetal_Hit)();

void GigaMetal_EnemyInfoHook();

#define OBJ_GIGAMETAL_SETUP \
  IMPORT_PUBLIC_FUNC(GigaMetal_StateBody_Marching); \
  IMPORT_PUBLIC_FUNC(GigaMetal_Hit); \
  REGISTER_ENEMY(GigaMetal)

#else

#define OBJ_GIGAMETAL_SETUP

#endif

#endif //! OBJ_GIGAMETAL_H
