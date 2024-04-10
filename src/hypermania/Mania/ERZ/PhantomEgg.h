#ifndef OBJ_PHANTOMEGG_H
#define OBJ_PHANTOMEGG_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitbox;
	uint16 aniFrames;
} ObjectPhantomShield;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	bool32 shieldActive;
	int32 blendAmount;
	int32 playerTimer[PLAYER_COUNT];
	Entity* parent;
	Animator animator;
} EntityPhantomShield;

extern ObjectPhantomShield* PhantomShield;

typedef enum {
	PHANTOMEGG_EGGMAN,
} PhantomEggTypes;

typedef enum {
	PHANTOMEGG_ATTACK_NONE,
	PHANTOMEGG_ATTACK_JUMP,
	PHANTOMEGG_ATTACK_SHOCK,
	PHANTOMEGG_ATTACK_MISSILES,
	PHANTOMEGG_ATTACK_WARP,
} PhantomEggAttackIDs;

typedef struct {
	RSDK_OBJECT
	TABLE(int32 debrisInfo[29], { 4,        0, 0, -0x20000, -0x28000, 1, 0, -0x20000, -0x28000, 2, 0, 0x20000, -0x20000, 3, 0, 0x28000,
	                              -0x20000, 4, 0, -0x10000, -0x10000, 5, 0, 0x10000,  -0x10000, 6, 0, -0x8000, -0x10000 });
	TABLE(int32 attackStateTable1[32], { 0, 0, 0, 0, 1, 0, 0, 2, 0, 1, 3, 0, 2, 0, 0, 4, 0, 0, 1, 0, 2, 0, 0, 3, 0, 0, 1, 0, 0, 2, 0, 4 });
	TABLE(int32 attackStateTable2[32], { 0, 0, 2, 0, 1, 3, 0, 2, 0, 0, 3, 0, 2, 0, 0, 3, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 1, 0, 0, 2, 0, 4 });
	TABLE(int32 attackStateTable3[32], { 0, 0, 2, 0, 1, 3, 3, 2, 0, 3, 3, 0, 2, 0, 0, 3, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 1, 0, 0, 2, 0, 4 });
	int32 boundsL;
	int32 boundsR;
	int32 boundsM;
	int32 boundsT;
	int32 boundsB;
	int32 boundsStoreL1;
	int32 boundsStoreR1;
	int32 boundsStoreT1;
	int32 boundsStoreB1;
	int32 startScanline;
	int32 endScanline;
	bool32 setupPalette;
	bool32 savedGameProgress;
	uint16 sfxHit;
	uint16 sfxExplosion2;
	uint16 sfxRocketJet;
	uint16 sfxExplosion3;
	uint16 sfxJump;
	uint16 sfxLand;
	uint16 sfxRepel;
	uint16 sfxShield;
	uint16 sfxShock;
	uint16 sfxSummon;
	uint16 sfxMissile;
	uint16 aniFrames;
	bool32 disableSuperForm;
} ObjectPhantomEgg;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 type;
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 remainingJumps;
	int32 attackTimer;
	int32 phantomID;
	int32 palBlendPercent;
	Vector2 targetPos;
	Vector2 targetVelocity;
	int32* attackStateTable;
	int32 unused;
	Animator crackAnimator;
	Animator coreAnimator;
	Animator legAnimator;
	Animator armLAnimator;
	Animator armRAnimator;
	Animator eggmanAnimator;
	Animator rubyAnimator;
	Hitbox hitbox;
} EntityPhantomEgg;

extern ObjectPhantomEgg* PhantomEgg;

extern void (*PhantomEgg_State_MoveAround)();
extern void (*PhantomEgg_State_Attack_Jumped)();
extern void (*PhantomEgg_State_Attack_JumpLand)();
extern void (*PhantomEgg_State_Attack_JumpAttack)();
extern void (*PhantomEgg_State_Attack_CableShock)();
extern void (*PhantomEgg_Hit)();

void PhantomEgg_EnemyInfoHook();

#define OBJ_PHANTOMEGG_SETUP \
  MOD_REGISTER_OBJECT_HOOK(PhantomShield); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_MoveAround); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_Attack_Jumped); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_Attack_JumpLand); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_Attack_JumpAttack); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_State_Attack_CableShock); \
  IMPORT_PUBLIC_FUNC(PhantomEgg_Hit); \
  REGISTER_ENEMY(PhantomEgg)

#endif //! OBJ_PHANTOMEGG_H
