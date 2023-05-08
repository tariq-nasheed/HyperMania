#ifndef OBJ_PHANTOMSHINOBI_H
#define OBJ_PHANTOMSHINOBI_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitbox;
	uint16 aniFrames;
	uint16 sfxBlade;
	uint16 sfxHit;
} ObjectPhantomShinobi;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	int32 timer;
	int32 invincibilityTimer;
	int32 unused;
	int32 finRadius;
	int32 rotStore;
	int32 rotSpeed;
	int32 numBounces;
	int32 attackCount;
	bool32 prevOnGround;
	Hitbox outerBox;
	Hitbox innerBox;
	Animator bodyAnimator;
	Animator armAnimator;
	Animator finAnimator;
} EntityPhantomShinobi;

extern ObjectPhantomShinobi* PhantomShinobi;

extern void (*PhantomShinobi_State_SetupAttack)();
extern void (*PhantomShinobi_State_Moving)();
extern void (*PhantomShinobi_State_PrepareFinAttack)();
extern void (*PhantomShinobi_State_ExtendFins)();
extern void (*PhantomShinobi_State_RetractFins)();
extern void (*PhantomShinobi_Hit)();

void PhantomShinobi_EnemyInfoHook();

#define OBJ_PHANTOMSHINOBI_SETUP \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_SetupAttack); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_Moving); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_PrepareFinAttack); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_ExtendFins); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_State_RetractFins); \
  IMPORT_PUBLIC_FUNC(PhantomShinobi_Hit); \
  REGISTER_ENEMY(PhantomShinobi)

#endif //! OBJ_PHANTOMSHINOBI_H
