#ifndef OBJ_SPECIALRING_H
#define OBJ_SPECIALRING_H

#include "GameAPI/Game.h"

typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
	Hitbox hitbox;
	uint16 sfxSpecialRing;
	uint16 sfxSpecialWarp;
	uint16 modelIndex;
	uint16 sceneIndex;
} ObjectSpecialRing;

typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 id;
	int32 planeFilter;
	int32 warpTimer;
	int32 sparkleRadius;
	Animator warpAnimator;
	int32 angleZ;
	int32 angleY;
	bool32 enabled;
	Matrix matTempRot;
	Matrix matTransform;
	Matrix matWorld;
	Matrix matNormal;
} EntitySpecialRing;

extern ObjectSpecialRing* SpecialRing;

// Imported Functions
extern void (*SpecialRing_State_Flash)(void);

// Overload Functions
void SpecialRing_Draw_Hook(void);
bool32 SpecialRing_State_Idle(bool32);
bool32 SpecialRing_State_Warp_Hook(bool32);

#endif //! OBJ_SPECIALRING_H
