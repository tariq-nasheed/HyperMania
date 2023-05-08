#ifndef OBJ_PHANTOMMYSTIC_H
#define OBJ_PHANTOMMYSTIC_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
	uint16 sfxCupSwap;
	uint16 sfxBigLaser;
	uint16 sfxImpact;
} ObjectPhantomMystic;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	Vector2 originPos;
	Vector2 mysticPos;
	int32 mysticVelY;
	int32 middleCupY;
	int32 timer;
	int32 invincibilityTimer;
	int32 correctCup;
	int32 cupPos[3];
	int32 unused1[3];
	int32 unused2[3];
	int32 cupAlpha[3];
	int32 swapCup1;
	int32 swapCup2;
	int32 swapCup1Pos;
	int32 swapCup2Pos;
	int32 swapCup1Alpha;
	int32 swapCup2Alpha;
	int32 cupSwapCount;
	Animator mysticAnimator;
	Animator cupAnimator;
	Animator cupSilhouetteAnimator;
	Animator cupSpikeAnimator; // Not actually ever drawn...
	Animator cupBlastAnimator;
	Hitbox hitbox;
} EntityPhantomMystic;

extern ObjectPhantomMystic* PhantomMystic;

extern void (*PhantomMystic_State_CupBlast)();
extern void (*PhantomMystic_State_MoveCupsToMystic)();
extern void (*PhantomMystic_Hit)();

void PhantomMystic_EnemyInfoHook();

#define OBJ_PHANTOMMYSTIC_SETUP \
  IMPORT_PUBLIC_FUNC(PhantomMystic_State_CupBlast); \
  IMPORT_PUBLIC_FUNC(PhantomMystic_State_MoveCupsToMystic); \
  IMPORT_PUBLIC_FUNC(PhantomMystic_Hit); \
  REGISTER_ENEMY(PhantomMystic)

#endif //! OBJ_PHANTOMMYSTIC_H
