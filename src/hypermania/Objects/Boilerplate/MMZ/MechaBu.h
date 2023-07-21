#ifndef OBJ_MECHABU_H
#define OBJ_MECHABU_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	TABLE(int32 sawOffsets[10], { -0x150000, -0xF0000, -0x170000, -0xE0000, -0x190000, -0xA0000, -0x1A0000, -0x50000, -0x1A0000, -0x40000 });
	Hitbox hitboxSaw;
	Hitbox hitboxUnused;
	uint16 aniFrames;
	uint16 sfxSawUp;
	uint16 sfxSawDown;
} ObjectMechaBu;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	ManiaPlaneFilterTypes planeFilter;
	uint8 timer;
	uint8 sawTimer;
	Vector2 startPos;
	uint8 startDir;
	Vector2 sawPos;
	Animator badnikAnimator;
	Animator hornAnimator;
	Animator sawAnimator;
} EntityMechaBu;

extern ObjectMechaBu* MechaBu;

extern void (*MechaBu_State_Moving)();
extern void (*MechaBu_State_Stopped)();
extern void (*MechaBu_State_Falling)();

void MechaBu_EnemyInfoHook();

#define OBJ_MECHABU_SETUP \
  IMPORT_PUBLIC_FUNC(MechaBu_State_Moving); \
  IMPORT_PUBLIC_FUNC(MechaBu_State_Stopped); \
  IMPORT_PUBLIC_FUNC(MechaBu_State_Falling); \
  REGISTER_ENEMY(MechaBu)

#endif //! OBJ_MECHABU_H
