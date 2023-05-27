#ifndef OBJ_AMOEBADROID_H
#define OBJ_AMOEBADROID_H

#include "GameAPI/Game.h"

#define AMOEBADROID_BLOB_COUNT (8)

typedef struct {
	RSDK_OBJECT
	TABLE(int32 debrisInfo1[17], { 4, 0, 0, -0x20000, -0x28000, 1, 0, 0x20000, -0x28000, 2, 0, -0x28000, -0x20000, 3, 0, 0x28000, -0x20000 });
	TABLE(int32 debrisInfo2[13], { 3, 4, 0, 0, -0x20000, 5, 0, -0x28000, -0x20000, 5, 1, 0x28000, -0x20000 });
	int32 boundsL;
	int32 boundsR;
	int32 boundsM;
	int32 boundsT;
	int32 boundsB;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxGather;
	uint16 sfxBounce;
	uint16 sfxRelease;
	uint16 aniFrames;
	uint16 waterFrames;
} ObjectAmoebaDroid;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 type;
	int32 timer;
	int32 invincibleTimer;
	int32 health;
	int32 blobAngleX;
	int32 blobAngleY;
	int32 blobAmplitude;
	int32 blobRadius;
	Vector2 offsetPos;
	Entity* blobs[AMOEBADROID_BLOB_COUNT];
	Entity* parent;
	Animator animator;
	Animator attractorTopAnimator;
	Animator attractorSideAnimator;
	Hitbox hitbox;
} EntityAmoebaDroid;

extern ObjectAmoebaDroid* AmoebaDroid;

extern void (*AmoebaDroid_State_DropIn)();
extern void (*AmoebaDroid_State_DropIntoPool)();
extern void (*AmoebaDroid_State_SurfaceFromPool)();
extern void (*AmoebaDroid_State_ChooseAttack)();
extern void (*AmoebaDroid_State_ExitPool)();
extern void (*AmoebaDroid_State_BounceAttack)();
extern void (*AmoebaDroid_State_GatherBlobs)();
extern void (*AmoebaDroid_State_SpinBlobs)();
extern void (*AmoebaDroid_Hit)();

void AmoebaDroid_EnemyInfoHook();

#define OBJ_AMOEBADROID_SETUP \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_DropIn); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_DropIntoPool); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_SurfaceFromPool); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_ChooseAttack); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_ExitPool); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_BounceAttack); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_GatherBlobs); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_State_SpinBlobs); \
  IMPORT_PUBLIC_FUNC(AmoebaDroid_Hit); \
  REGISTER_ENEMY(AmoebaDroid)

#endif //! OBJ_AMOEBADROID_H
