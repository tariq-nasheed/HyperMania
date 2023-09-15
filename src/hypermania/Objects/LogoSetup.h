#ifndef OBJ_LOGOSETUP_H
#define OBJ_LOGOSETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
	RSDK_OBJECT
	int32 timer;
	uint16 sfxSega;
} ObjectLogoSetup;

// Entity Class
typedef struct {
	RSDK_ENTITY
	StateMachine(state);
	StateMachine(stateDraw);
	int32 timer;
} EntityLogoSetup;

// Object Struct
extern ObjectLogoSetup* LogoSetup;

// Imported Functions
extern void (*LogoSetup_State_NextLogos)();
extern void (*LogoSetup_State_ShowLogos)();
extern void (*LogoSetup_Draw_Fade)();

#define OBJ_LOGOSETUP_SETUP \
  IMPORT_PUBLIC_FUNC(LogoSetup_State_NextLogos); \
  IMPORT_PUBLIC_FUNC(LogoSetup_State_ShowLogos); \
  IMPORT_PUBLIC_FUNC(LogoSetup_Draw_Fade); \
  MOD_REGISTER_OBJECT_HOOK(LogoSetup)

#endif //! OBJ_LOGOSETUP_H
