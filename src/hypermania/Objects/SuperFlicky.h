#ifndef OBJ_SUPERFLICKY_H
#define OBJ_SUPERFLICKY_H

#include "GameAPI/Game.h"

// Constants
#define SUPERFLICKY_COUNT (4)
#define SUPERFLICKY_COLOR_COUNT (6)

// Object Class
typedef struct {
	RSDK_OBJECT
	Hitbox hitbox;
	uint16 aniFrames;
	int32 sfxFlee;
} ObjectSuperFlicky;

// Entity Class
typedef struct {
	RSDK_ENTITY
	struct { int16 amount, state; } blend;
	EntityPlayer* player;
	uint8 instanceOsc[SUPERFLICKY_COUNT];
	uint8 instanceCooldown[SUPERFLICKY_COUNT];
	Vector2 instancePos[SUPERFLICKY_COUNT];
	Vector2 instanceVel[SUPERFLICKY_COUNT];
	Entity* instanceTarget[SUPERFLICKY_COUNT];
	Animator instanceAnimator[SUPERFLICKY_COUNT];
} EntitySuperFlicky;

// Object Struct
extern ObjectSuperFlicky* SuperFlicky;

// Standard Entity Events
void SuperFlicky_Update(void);
void SuperFlicky_LateUpdate(void);
void SuperFlicky_StaticUpdate(void);
void SuperFlicky_Draw(void);
void SuperFlicky_Create(void* data);
void SuperFlicky_StageLoad(void);
void SuperFlicky_EditorDraw(void);
void SuperFlicky_EditorLoad(void);
void SuperFlicky_Serialize(void);

// Extra Entity Functions
void SuperFlicky_HandleAttack(int32 slot);
void SuperFlicky_TryFindValidTarget(int32 slot);
void SuperFlicky_BlendSuperPalette(int32 bankID);

// Reserved Slot
extern int16 SuperFlickySlot;

#endif //! OBJ_SUPERFLICKY_H