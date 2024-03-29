#ifndef OBJ_JUGGLESAW_H
#define OBJ_JUGGLESAW_H

#include "GameAPI/Game.h"

typedef enum { JUGGLESAW_NO_SAW = 0, JUGGLESAW_HAS_SAW = 1, JUGGLESAW_AWAITING_SAW = 2 } JuggleSawMode;

#define JUGGLESAW_MAX_FRIENDS (8)

typedef struct {
	RSDK_OBJECT
	Hitbox hitboxBadnik;
	Hitbox hitboxFriendRange;
	Hitbox hitboxSaw;
	Hitbox hitboxGrabV;
	Hitbox hitboxGrabH;
	uint16 aniFrames;
	uint16 sfxExplode;
	uint16 sfxJuggle;
	uint16 sfxThrow;
} ObjectJuggleSaw;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	uint16 sawDelay;
	uint32 sawSpeed;
	bool32 hasSaw;
	uint16 setID;
	void* friends[JUGGLESAW_MAX_FRIENDS];
	uint8 friendCount;
	uint8 sawTimer;
	Vector2 startPos;
	uint8 startDir;
	Animator animator;
} EntityJuggleSaw;

extern ObjectJuggleSaw* JuggleSaw;

extern void (*JuggleSaw_StateCrab_Handle)();
extern void (*JuggleSaw_StateCrab_ThrowSaw)();

void JuggleSaw_EnemyInfoHook();

#define OBJ_JUGGLESAW_SETUP \
  IMPORT_PUBLIC_FUNC(JuggleSaw_StateCrab_Handle); \
  IMPORT_PUBLIC_FUNC(JuggleSaw_StateCrab_ThrowSaw); \
  REGISTER_ENEMY(JuggleSaw)

#endif //! OBJ_JUGGLESAW_H
