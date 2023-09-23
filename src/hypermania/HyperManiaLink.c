#include "HyperManiaLink.h"

HMFuncTable HMAPI;

void LinkHyperManiaAPI() {
	HMAPI.InitClient         = Mod.GetPublicFunction("HyperMania", "HMAPI_InitClient");
	HMAPI.GetGlobals         = Mod.GetPublicFunction("HyperMania", "HMAPI_GetGlobals");
	HMAPI.AddCharacter       = Mod.GetPublicFunction("HyperMania", "HMAPI_AddCharacter");
	HMAPI.ScreenFlash        = Mod.GetPublicFunction("HyperMania", "HMAPI_ScreenFlash");
	HMAPI.BadnikScreenClear  = Mod.GetPublicFunction("HyperMania", "HMAPI_BadnikScreenClear");
	HMAPI.ItemBoxScreenClear = Mod.GetPublicFunction("HyperMania", "HMAPI_ItemBoxScreenClear");
	HMAPI.SaveFile           = Mod.GetPublicFunction("HyperMania", "HM_Save_SaveFile");
	HMAPI.LoadFile           = Mod.GetPublicFunction("HyperMania", "HM_Save_LoadFile");
	HMAPI.AllocExtMem        = Mod.GetPublicFunction("HyperMania", "AllocExtMem");
	HMAPI.GetExtMem          = Mod.GetPublicFunction("HyperMania", "GetExtMem");
	HMAPI.FreeExtMem         = Mod.GetPublicFunction("HyperMania", "FreeExtMem");
	HMAPI.IsPlayerHyper      = Mod.GetPublicFunction("HyperMania", "Player_IsHyper");
	HMAPI.AddATKClass        = Mod.GetPublicFunction("HyperMania", "AddATKClass");
	HMAPI.GetATKClassInfo    = Mod.GetPublicFunction("HyperMania", "GetATKClassInfo");
	HMAPI.IsATKEntity        = Mod.GetPublicFunction("HyperMania", "IsATKEntity");
}