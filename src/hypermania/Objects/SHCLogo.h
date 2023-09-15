#ifndef OBJ_SHCLOGO_H
#define OBJ_SHCLOGO_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
	RSDK_OBJECT
	uint16 aniFrames;
	int32 sfxSplash;
} ObjectSHCLogo;

// Entity Class
typedef struct {
	RSDK_ENTITY
	Animator animator;
	int32 timer;
} EntitySHCLogo;

// Object Struct
extern ObjectSHCLogo* SHCLogo;

// Standard Entity Events
void SHCLogo_Update();
void SHCLogo_LateUpdate();
void SHCLogo_StaticUpdate();
void SHCLogo_Draw();
void SHCLogo_Create(void* data);
void SHCLogo_StageLoad();
#if RETRO_INCLUDE_EDITOR
void SHCLogo_EditorDraw();
void SHCLogo_EditorLoad();
#endif
void SHCLogo_Serialize();

// Extra Entity Functions
bool32 LogoSetup_State_FadeToNextLogos_HOOK(bool32 skippedState);
bool32 LogoSetup_State_ShowLogos_HOOK(bool32 skippedState);
bool32 LogoSetup_State_NextLogos_HOOK(bool32 skippedState);

#endif //! OBJ_SHCLOGO_H