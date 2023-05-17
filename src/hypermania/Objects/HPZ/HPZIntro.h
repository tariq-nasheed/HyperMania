#ifndef OBJ_HPZINTRO_H
#define OBJ_HPZINTRO_H

#include "GameAPI/Game.h"

#define HPZ_TRANSFER_DELAY 30

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
	int32 timer;
	int32 beams;
	int32 emeraldAngle[7];
	Vector2 emeraldOffset[7];
	Animator animatorEmeralds[7];
	bool32 flying_off;
} EntityHPZIntro;


//asdopfkasudfasdf
extern Entity* SortedSuperEmeralds[8];

// Object Struct
extern ObjectHPZIntro* HPZIntro;

// Standard Entity Events
void HPZIntro_Update(void);
void HPZIntro_LateUpdate(void);
void HPZIntro_StaticUpdate(void);
void HPZIntro_Draw(void);
void HPZIntro_Create(void *data);
void HPZIntro_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void HPZIntro_EditorDraw(void);
void HPZIntro_EditorLoad(void);
#endif
void HPZIntro_Serialize(void);

#endif //! OBJ_HPZINTRO_H
