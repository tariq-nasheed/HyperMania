#include "ModLink.h"

void LinkHyperManiaAPI() {
	HMAPI.InitClient         = Mod.GetPublicFunction(modID, "HMAPI_InitClient");
	HMAPI.GetGlobals         = Mod.GetPublicFunction(modID, "HMAPI_GetGlobals");
	HMAPI.AddCharacter       = Mod.GetPublicFunction(modID, "HMAPI_AddCharacter");
	HMAPI.ScreenFlash        = Mod.GetPublicFunction(modID, "HMAPI_ScreenFlash");
	HMAPI.BadnikScreenClear  = Mod.GetPublicFunction(modID, "HMAPI_BadnikScreenClear");
	HMAPI.ItemBoxScreenClear = Mod.GetPublicFunction(modID, "HMAPI_ItemBoxScreenClear");
	HMAPI.SaveFile           = Mod.GetPublicFunction(modID, "HM_Save_SaveFile");
	HMAPI.LoadFile           = Mod.GetPublicFunction(modID, "HM_Save_LoadFile");
	HMAPI.AllocExtMem        = Mod.GetPublicFunction(modID, "AllocExtMem");
	HMAPI.GetExtMem          = Mod.GetPublicFunction(modID, "GetExtMem");
	HMAPI.FreeExtMem         = Mod.GetPublicFunction(modID, "FreeExtMem");
	HMAPI.IsPlayerHyper      = Mod.GetPublicFunction(modID, "Player_IsHyper");
	HMAPI.AddATKClass        = Mod.GetPublicFunction(modID, "AddATKClass");
	HMAPI.GetATKClassInfo    = Mod.GetPublicFunction(modID, "GetATKClassInfo");
	HMAPI.IsATKEntity        = Mod.GetPublicFunction(modID, "IsATKEntity");
}