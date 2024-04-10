#ifndef OBJ_WOODROW_H
#define OBJ_WOODROW_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxFullRange;
	Hitbox hitboxBombRange;
	Hitbox hitboxBomb;
	uint16 aniFrames;
	uint16 sfxExplosion;
	uint16 sfxPeck;
} ObjectWoodrow;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 type;
	int32 distUp;
	int32 distDown;
	uint8 activeBombCount;
	uint8 bombCount;
	uint8 bombFallDelay;
	uint8 moveDelay;
	int32 rangeMask;
	Vector2 startPos;
	uint8 startDir;
	void* parent;
	Animator animator;
} EntityWoodrow;

extern ObjectWoodrow* Woodrow;

extern void (*Woodrow_State_Idle)();
extern void (*Woodrow_State_MoveUp)();
extern void (*Woodrow_State_MoveDown)();

void Woodrow_EnemyInfoHook();

#define OBJ_WOODROW_SETUP \
  IMPORT_PUBLIC_FUNC(Woodrow_State_Idle); \
  IMPORT_PUBLIC_FUNC(Woodrow_State_MoveUp); \
  IMPORT_PUBLIC_FUNC(Woodrow_State_MoveDown); \
  REGISTER_ENEMY(Woodrow)

#endif //! OBJ_WOODROW_H
