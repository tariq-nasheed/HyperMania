#ifndef OBJ_HPZSETUP_H
#define OBJ_HPZSETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
	RSDK_OBJECT
} ObjectHPZSetup;

// Entity Class
typedef struct {
	RSDK_ENTITY
} EntityHPZSetup;

// Object Struct
extern ObjectHPZSetup* HPZSetup;

// Standard Entity Events
void HPZSetup_Update(void);
void HPZSetup_LateUpdate(void);
void HPZSetup_StaticUpdate(void);
void HPZSetup_Draw(void);
void HPZSetup_Create(void *data);
void HPZSetup_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void HPZSetup_EditorDraw(void);
void HPZSetup_EditorLoad(void);
#endif
void HPZSetup_Serialize(void);

#endif //! OBJ_HPZSETUP_H
