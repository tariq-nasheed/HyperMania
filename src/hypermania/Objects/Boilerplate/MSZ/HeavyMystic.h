#ifndef OBJ_HEAVYMYSTIC_H
#define OBJ_HEAVYMYSTIC_H

#include "GameAPI/Game.h"

typedef enum {
	MYSTIC_MISCHIEF,
	MYSTIC_BOSS,
	MYSTIC_BOX,
	MYSTIC_CORK,
	MYSTIC_BOMB,
	MYSTIC_DEBRIS,
} HeavyMysticTypes;

typedef struct {
	RSDK_OBJECT
	int32 boundsL;
	int32 boundsR;
	int32 boundsM;
	int32 boundsT;
	int32 boundsB;
	int32 curtainLinePos;
	uint16 sfxAssemble;
	uint16 sfxMagicBox;
	uint16 sfxClack;
	uint16 sfxPowerDown;
	uint16 sfxImpact;
	uint16 sfxPon;
	uint16 sfxDrop;
	uint16 sfxImpact2;
	uint16 sfxHit;
	uint16 sfxExplosion;
	uint16 sfxPoof;
	uint16 sfxTwinkle;
	uint16 sfxHat;
	uint16 sfxHatNode;
	uint16 sfxBleeps;
	uint16 sfxTransform;
	uint16 sfxAppear1;
	uint16 aniFrames;
	uint16 rouguesFrames;
} ObjectHeavyMystic;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 type;
	int32 timer;
	int32 invincibilityTimer;
	int32 health;
	int32 rougeHealth;
	int32 particleFXTimer;
	int32 unused;
	int32 attackID;
	int32 rougeID;
	Vector2 targetPos;
	Animator animator;
	Hitbox hitbox;
} EntityHeavyMystic;

extern ObjectHeavyMystic* HeavyMystic;

extern void (*HeavyMystic_StateBoss_RougeHit)();
extern void (*HeavyMystic_StateBoss_MysticReveal)();
extern void (*HeavyMystic_StateBoss_FangIdle)();
extern void (*HeavyMystic_StateBoss_FangTell)();
extern void (*HeavyMystic_StateBoss_FangHop)();
extern void (*HeavyMystic_StateBoss_BarkIdle)();
extern void (*HeavyMystic_StateBoss_BarkPounding)();
extern void (*HeavyMystic_StateBoss_BarkJump)();
extern void (*HeavyMystic_StateBoss_BeanIdle)();
extern void (*HeavyMystic_StateBoss_BeanBomb1Throw)();
extern void (*HeavyMystic_StateBoss_BeanBomb2Throw)();
extern void (*HeavyMystic_StateBoss_BeanJump)();
extern void (*HeavyMystic_Hit)();

void HeavyMystic_EnemyInfoHook();

#define OBJ_HEAVYMYSTIC_SETUP \
  IMPORT_PUBLIC_FUNC(HeavyMystic_Hit); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_RougeHit); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_MysticReveal); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_FangIdle); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_FangTell); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_FangHop); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BarkIdle); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BarkPounding); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BarkJump); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BeanIdle); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BeanBomb1Throw); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BeanBomb2Throw); \
  IMPORT_PUBLIC_FUNC(HeavyMystic_StateBoss_BeanJump); \
  REGISTER_ENEMY(HeavyMystic)

#endif //! OBJ_HEAVYMYSTIC_H
