#ifndef OBJ_ICEBOMBA_H
#define OBJ_ICEBOMBA_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxBomb;
	Hitbox hitboxRange;
	uint16 aniFrames;
	uint16 sfxExplosion;
	uint16 sfxFreeze;
} ObjectIceBomba;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 dir;
	uint16 dist;
	uint16 dip;
	uint8 startDir;
	Vector2 startPos;
	uint32 startDist;
	Animator bodyAnimator;
	Animator wingAnimator;
	Animator bombAnimator;
} EntityIceBomba;

extern ObjectIceBomba* IceBomba;

extern void (*IceBomba_State_Flying)();
extern void (*IceBomba_State_Turning)();
extern void (*IceBomba_State_FlyAway)();

void IceBomba_EnemyInfoHook();

#define OBJ_ICEBOMBA_SETUP \
  IMPORT_PUBLIC_FUNC(IceBomba_State_Flying); \
  IMPORT_PUBLIC_FUNC(IceBomba_State_Turning); \
  IMPORT_PUBLIC_FUNC(IceBomba_State_FlyAway); \
  REGISTER_ENEMY(IceBomba)

#endif //! OBJ_ICEBOMBA_H
