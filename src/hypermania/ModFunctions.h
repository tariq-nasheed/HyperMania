#ifndef MODFUNCTIONS_H
#define MODFUNCTIONS_H

#include "HyperManiaVariables.h"

#include "Objects/Player.h"
#include "Objects/Boilerplate/SaveGame.h"
#include "Objects/Boilerplate/Animals.h"
#include "Objects/Boilerplate/Camera.h"
#include "Objects/Boilerplate/CollapsingPlatform.h"
#include "Objects/Boilerplate/Debris.h"
#include "Objects/Boilerplate/Explosion.h"
#include "Objects/Boilerplate/FXFade.h"
#include "Objects/Boilerplate/ItemBox.h"
#include "Objects/Boilerplate/Ring.h"
#include "Objects/Boilerplate/ScoreBonus.h"
#include "Objects/Boilerplate/Zone.h"
#include "Boilerplate/Music.h"
#include "Boilerplate/Global/PauseMenu.h"
#include "Boilerplate/Global/InvincibleStars.h"

#include "Objects/Boilerplate/CPZ/CPZSetup.h"
#include "Objects/Boilerplate/OOZ/OOZSetup.h"
#include "Objects/Boilerplate/HCZ/HCZSetup.h"
#include "Objects/Boilerplate/MMZ/FarPlane.h"
#include "Objects/Boilerplate/ERZ/ERZStart.h"
#include "Objects/Boilerplate/BSS/BSS_Setup.h"


extern bool32 HPZ_SuperSpecialStage; // bad hack variable for testing purposes, will be removed later, please understand
extern SaveRAM* GetSaveRAM_Safe(); // this really shouldnt be here but whatever

HM_SaveRAM* HM_Save_GetDataPtr(int32 slot, bool32 encore);
void HM_Save_SaveFile();
void HM_Save_LoadFile();

// =============================================================================

// Extension variables for preexisting objects ---------------------------------

// =============================================================================
#define EXTMEM_FREE_ID -1
#define MAX_EXTMEM_ENTITIES 64

extern extmem_t ExtMemory[MAX_EXTMEM_ENTITIES];
extern uint32   ExtMemory_size;
extern int8 ExtMemoryIndex[ENTITY_COUNT - TEMPENTITY_COUNT];
extern int8 ExtMemoryRevIndex[MAX_EXTMEM_ENTITIES];

void* AllocExtMem(int32 owner_id, uint32 bytes);
void* GetExtMem(int32 owner_id);
void FreeExtMem(int32 owner_id);

// =============================================================================

// Attackable Classes ----------------------------------------------------------

// =============================================================================
#define ADD_ATTACKABLE_CLASS(id, vulnerable_func, hitbox_func, hit_func, pos_func, flags) \
  AddATKClass(id, (attackinfo_t){ vulnerable_func, hitbox_func, hit_func, pos_func, flags })

extern void (*APICallback_TrackEnemyDefeat)(uint8 zoneID, uint8 actID, uint8 playerID, int32 x, int32 y);
extern void (*TimeAttackData_TrackEnemyDefeat)(StatInfo* stat, uint8 zoneID, uint8 actID, uint8 characterID, bool32 encore, int32 x, int32 y);

bool32 AddATKClass(uint16 id, attackinfo_t info);
attackinfo_t* GetATKClassInfo(uint16 id);
attackinfo_t* IsATKEntity(Entity* entity, uint8 blacklist_mask, bool32 checkVisible);
bool32 Generic_CheckVulnerable(Entity* self);
Hitbox* Generic_GetHitbox(Entity* self);
void Generic_OnHit(EntityPlayer* player, Entity* self);
void Generic_BadnikBreak_NoEntity(EntityPlayer* player, Vector2 position, bool32 spawnAnimals);
void Generic_BadnikBreak(EntityPlayer* player, Entity* entity, bool32 spawnAnimals);

// =============================================================================

// API -------------------------------------------------------------------------

// =============================================================================
typedef struct {
	uint16 id;
	hyperpal_t* paletteInfo;
} playerinfo_t;

typedef struct {
	const char* modID;
	uint16* clearFrames;
	struct {
		int32 count;
		playerinfo_t* mem;
	} players;
} clientinfo_t;

typedef struct {
	size_t len;
	clientinfo_t* mem;
} clientarray_t;

extern clientarray_t clients;

bool32 HMAPI_InitClient(const char* _modID, uint16* clearFrames);
HM_global_t* HMAPI_GetGlobals();
bool32 HMAPI_AddCharacter(const char* _modID, uint16 characterID, hyperpal_t* paletteInfo);
void HMAPI_ScreenFlash(EntityPlayer* player, float intensity);
void HMAPI_BadnikScreenClear(EntityPlayer* player);
void HMAPI_ItemBoxScreenClear(EntityPlayer* player, bool32 force);
void AddAPIFunctions();

#endif //MODFUNCTIONS_H