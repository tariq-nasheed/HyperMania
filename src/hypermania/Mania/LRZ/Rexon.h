#ifndef OBJ_REXON_H
#define OBJ_REXON_H

#include "GameAPI/Game.h"

#define REXON_SEGMENT_COUNT (5)

typedef enum {
	REXON_MAIN,
	REXON_DEBRIS,
	REXON_SHOT,
} RexonTypes;

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxShell;
	Hitbox hitboxRange;
	Hitbox hitboxProjectile;
	uint16 aniFrames;
	uint16 sfxShot;
	uint16 sfxExplosion;
} ObjectRexon;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	bool32 noMove;
	int32 type;
	Vector2 startPos;
	uint8 startDir;
	Vector2 positions[REXON_SEGMENT_COUNT + 1]; // neck + head
	int32 segmentMagnitude[REXON_SEGMENT_COUNT];
	int32 segmentAmplitude[REXON_SEGMENT_COUNT];
	uint8 segmentDirections[REXON_SEGMENT_COUNT];
	uint8 segmentID;
	int32 timer;
	int32 destroyDelay;
	Animator bodyAnimator;
	Animator neckAnimator;
	Animator headAnimator;
} EntityRexon;

extern ObjectRexon* Rexon;

extern void (*Rexon_State_Hidden)();
extern void (*Rexon_State_Rising)();
extern void (*Rexon_State_Shooting)();
extern void (*Rexon_State_Destroyed)();

void Rexon_EnemyInfoHook();

#define OBJ_REXON_SETUP \
  IMPORT_PUBLIC_FUNC(Rexon_State_Hidden); \
  IMPORT_PUBLIC_FUNC(Rexon_State_Rising); \
  IMPORT_PUBLIC_FUNC(Rexon_State_Shooting); \
  IMPORT_PUBLIC_FUNC(Rexon_State_Destroyed); \
  REGISTER_ENEMY(Rexon)

#endif //! OBJ_REXON_H
