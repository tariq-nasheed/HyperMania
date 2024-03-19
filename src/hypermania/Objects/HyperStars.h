#ifndef OBJ_HYPERSTARS_H
#define OBJ_HYPERSTARS_H

#include "GameAPI/Game.h"

// Constants
#define HYPERSTARS_COUNT (4)

// Object Class
typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
} ObjectHyperStars;

// Entity Class
typedef struct {
	RSDK_ENTITY
	EntityPlayer* player;
	uint8 instanceOsc[HYPERSTARS_COUNT];
	int8 instanceTimer[HYPERSTARS_COUNT];
	Vector2 instancePos[HYPERSTARS_COUNT];
	Vector2 instanceVel[HYPERSTARS_COUNT];
	Animator instanceAnimator[HYPERSTARS_COUNT];
} EntityHyperStars;

// Object Struct
extern ObjectHyperStars* HyperStars;

// Standard Entity Events
void HyperStars_Update(void);
void HyperStars_LateUpdate(void);
void HyperStars_StaticUpdate(void);
void HyperStars_Draw(void);
void HyperStars_Create(void* data);
void HyperStars_StageLoad(void);
void HyperStars_EditorDraw(void);
void HyperStars_EditorLoad(void);
void HyperStars_Serialize(void);

#endif //! OBJ_HYPERSTARS_H