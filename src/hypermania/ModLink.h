#ifndef MODLINK_H
#define MODLINK_H

struct {
	bool32        (InitClient*)(const char* _modID, uint16* clearFrames);
	HM_global_t*  (GetGlobals*)();
	bool32        (AddCharacter*)(const char* _modID, uint16 characterID, hyperpal_t* paletteInfo);
	void          (ScreenFlash*)(EntityPlayer* player, float intensity);
	void          (BadnikScreenClear*)(EntityPlayer* player);
	void          (ItemBoxScreenClear*)(EntityPlayer* player, bool32 force);
	void          (SaveFile*)();
	void          (LoadFile*)();
	void*         (AllocExtMem*)(int32 owner_id, uint32 bytes);
	void*         (GetExtMem*)(int32 owner_id);
	void          (FreeExtMem*)(int32 owner_id);
	bool32        (IsPlayerHyper*)(EntityPlayer* player);
	bool32        (AddATKClass*)(uint16 id, attackinfo_t info);
	attackinfo_t* (GetATKClassInfo*)(uint16 id);
	attackinfo_t* (IsATKEntity*)(Entity* entity, uint8 blacklist_mask, bool32 checkVisible);
} HMAPI;

void LinkHyperManiaAPI();

#endif //MODLINK_H