#ifndef OBJ_METALSONIC_H
#define OBJ_METALSONIC_H

#include "GameAPI/Game.h"

typedef enum {
	MS_ANI_IDLE,
	MS_ANI_TAUNT,
	MS_ANI_READY,
	MS_ANI_HOVER,
	MS_ANI_HOVERTURN,
	MS_ANI_FLY,
	MS_ANI_DASHATTACK,
	MS_ANI_ELECTRICATTACK,
	MS_ANI_BALLATTACK,
	MS_ANI_ENTERPANEL,
	MS_ANI_DEFEATED,
	MS_ANI_BOOSTER_WEAK,
	MS_ANI_BOOSTER_STRONG,
	MS_ANI_BOOSTER_INTRO,
} MetalSonicAniIDs;

typedef enum {
	MS_ATTACK_DASH,
	MS_ATTACK_ELECTRIC,
	MS_ATTACK_BALL,
} MetalSonicAttackIDs;

typedef struct {
	RSDK_OBJECT
	int32 unused;
	int32 invincibilityTimerPanel;
	uint16 finishedAttacks;
	uint16 sfxHit;
	uint16 sfxExplosion2;
	uint16 sfxExplosion3;
	uint16 sfxRumble;
	uint16 sfxJump2;
	uint16 sfxSpecialRing;
	uint16 sfxMSElecPulse;
	uint16 sfxMSBall;
	uint16 sfxMSFireball;
	uint16 sfxBeep3;
	uint16 sfxBeep4;
	uint16 sfxRockemSockem;
	uint16 sfxMSShoot;
	uint16 sfxMSChargeFire;
#if MANIA_USE_PLUS
	uint16 sfxMSTransform;
	uint16 sfxTransform2;
#endif
	Hitbox hitboxHover;
	Hitbox hitboxDash;
	uint16 aniFrames;
} ObjectMetalSonic;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 targetPos;
	int32 timer;
	int32 unused1;
	int32 unused2;
	int32 health;
	int32 unused3;
	Vector2 hoverVelocity;
	Vector2 targetVelocity;
	int32 attackTimer;
	uint8 attackType;
	int32 unused4;
	int32 invincibilityTimer;
	Entity* panel;
	Vector2 unusedVec1;
	Vector2 unusedVec2;
	Vector2 unusedVec3;
	Hitbox* outerBox;
	Hitbox* innerBox;
	Animator metalSonicAnimator;
	Animator boosterAnimator;
} EntityMetalSonic;

extern ObjectMetalSonic* MetalSonic;

// hopefully this works because i dont feel like compiling a pre-mania Game.so to test it lol
#if !MANIA_USE_PLUS
  extern void (*MetalSonic_State_Hover_Phase2)();
  extern void (*MetalSonic_State_FinishAttack_Phase2)();
  extern void (*MetalSonic_Hit)();

  void MetalSonic_EnemyInfoHook();

  #define OBJ_METALSONIC_SETUP \
    IMPORT_PUBLIC_FUNC(MetalSonic_State_Hover_Phase2); \
    IMPORT_PUBLIC_FUNC(MetalSonic_State_FinishAttack_Phase2); \
    IMPORT_PUBLIC_FUNC(MetalSonic_Hit); \
    REGISTER_ENEMY(MetalSonic)
#else
  #define OBJ_METALSONIC_SETUP
#endif

#endif //! OBJ_METALSONIC_H
