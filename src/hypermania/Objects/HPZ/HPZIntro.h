#ifndef OBJ_HPZINTRO_H
#define OBJ_HPZINTRO_H

#include "GameAPI/Game.h"

enum HPZIntroDrawFlags {
	HPZI_NONE         = 0x00,
	HPZI_PLAYER_UP    = 0x01,
	HPZI_PLAYER_LEFT  = 0x02,
	HPZI_PLAYER_INVIS = 0x04,
	HPZI_EMERALDS     = 0x08
};

// Object Class
typedef struct {
	RSDK_OBJECT
	uint16 sfxTwinkle;
	uint16 sfxEmeraldFlying;
	uint16 aniFramesEmerald;
} ObjectHPZIntro;

// Entity Class
typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	int32 drawFlags;
	int32 timer;
	int32 beams;
	int32 emeraldAngle[7];
	Vector2 emeraldOffset[7];
	Animator animatorEmeralds[7];
	Entity* teleBeam;
} EntityHPZIntro;


//asdopfkasudfasdf
extern Entity* SortedSuperEmeralds[8];

// Object Struct
extern ObjectHPZIntro* HPZIntro;

// Standard Entity Events
void HPZIntro_Update();
void HPZIntro_LateUpdate();
void HPZIntro_StaticUpdate();
void HPZIntro_Draw();
void HPZIntro_Create(void *data);
void HPZIntro_StageLoad();
void HPZIntro_EditorDraw();
void HPZIntro_EditorLoad();
void HPZIntro_Serialize();

// States
void HPZIntro_State_TeleportPlayer();
void HPZIntro_State_RaiseEmeralds();
void HPZIntro_State_EmeraldsFlyOff();
void HPZIntro_State_ActivateSuperEmeralds();

#endif //! OBJ_HPZINTRO_H
