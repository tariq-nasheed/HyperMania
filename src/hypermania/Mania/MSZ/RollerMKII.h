#ifndef OBJ_ROLLERMKII_H
#define OBJ_ROLLERMKII_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxObject;
	Hitbox hitboxInner_Rolling;
	Hitbox hitboxOuter_Rolling;
	Hitbox hitboxInner_Idle;
	Hitbox hitboxOuter_Idle;
	uint16 aniFrames;
	uint16 sfxBumper;
	uint16 sfxJump;
	uint16 sfxDropDash;
	uint16 sfxRelease;
	uint16 sfxSkidding;
} ObjectRollerMKII;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	Vector2 startPos;
	uint8 startDir;
	uint8 timer;
	bool32 touchedGround;
	EntityPlayer* playerPtr;
	Animator animator;
} EntityRollerMKII;

extern ObjectRollerMKII* RollerMKII;

extern void (*RollerMKII_State_Idle)();
extern void (*RollerMKII_State_SpinUp)();

void RollerMKII_EnemyInfoHook();

#define OBJ_ROLLERMKII_SETUP \
  IMPORT_PUBLIC_FUNC(RollerMKII_State_Idle); \
  IMPORT_PUBLIC_FUNC(RollerMKII_State_SpinUp); \
  REGISTER_ENEMY(RollerMKII)

#endif //! OBJ_ROLLERMKII_H
