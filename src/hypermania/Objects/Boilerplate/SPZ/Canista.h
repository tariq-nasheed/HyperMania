#ifndef OBJ_CANISTA_H
#define OBJ_CANISTA_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxRange;
	Hitbox hitboxDetect;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
	uint16 sfxPon;
} ObjectCanista;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint8 triggerMode;
	Vector2 detectOffset;
	Vector2 detectSize;
	int32 shootOffset;
	int32 shootSize;
	int32 stopTimer;
	int32 detectDelay;
	EntityPlayer* detectedPlayer;
	Vector2 startPos;
	uint8 startDir;
	uint8 moveDir;
	uint8 timer;
	Hitbox hitboxDetect;
	int32 unused1;
	int32 unused2;
	Animator mainAnimator;
	Animator tapeAnimator;
	Animator cannonAnimator;
} EntityCanista;

extern ObjectCanista* Canista;

extern void (*Canista_State_Moving)();
extern void (*Canista_State_Idle)();

void Canista_EnemyInfoHook();

#define OBJ_CANISTA_SETUP \
  IMPORT_PUBLIC_FUNC(Canista_State_Moving); \
  IMPORT_PUBLIC_FUNC(Canista_State_Idle); \
  REGISTER_ENEMY(Canista)

#endif //! OBJ_CANISTA_H
