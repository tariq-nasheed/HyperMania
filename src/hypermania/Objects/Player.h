#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include "GameAPI/Game.h"

extern ObjectPlayer* Player;

// =============================================================================

// Mod Definitions -------------------------------------------------------------

// =============================================================================
#define TRACK_HYPER 15

typedef enum {
	HYPERBLEND_FADEIN = -1,
	HYPERBLEND_FADEOUT // unused for now
} HyperBlendStates;

typedef struct {
	uint16 shockwaveFrames;
	int32 sfxEarthquake;
	int32 sfxEarthquake2;
	int32 sfxJetGlide;
} PlayerStaticExt_t;

typedef struct {
	int32 prev_ID, prev_xvel;
	void* prev_state;
	struct { int16 state; int16 amount; } blend;
	int32 glide_timer;
	bool32 can_dash;
	bool32 is_hyper;
} PlayerExt;

extern PlayerStaticExt_t PlayerStaticExt;

// =============================================================================

// Functions -------------------------------------------------------------------

// =============================================================================
extern void (*Player_GiveScore)(EntityPlayer *player, int32 score);
extern void (*Player_GiveRings)(EntityPlayer *player, int32 amount, bool32 playSfx);
extern void (*Player_SpawnMightyHammerdropDust)(int32 speed, Hitbox *hitbox);
extern bool32 (*Player_CheckCollisionTouch)(EntityPlayer* player, void* e, Hitbox* entityHitbox);
extern bool32 (*Player_CheckCollisionPlatform)(EntityPlayer *player, void *entity, Hitbox *entityHitbox);
extern void (*Player_Gravity_True)();
extern void (*Player_HandleAirMovement)();
extern void (*Player_HandleAirFriction)();
extern void (*Player_State_Air)();
extern void (*Player_State_KnuxGlideLeft)();
extern void (*Player_State_KnuxGlideRight)();
extern void (*Player_State_KnuxWallClimb)();
extern void (*Player_Input_P2_AI)();
extern void (*Player_JumpAbility_Mighty)();
extern void (*Player_State_Static)();
extern void (*Player_State_Transform)();
extern void (*Player_State_Ground)();

bool32 Player_State_Ground_HOOK(bool32);
bool32 Player_JumpAbility_Sonic_HOOK(bool32);
bool32 Player_JumpAbility_Mighty_HOOK(bool32);
bool32 Player_State_MightyHammerDrop_HOOK(bool32);
bool32 Player_State_RayGlide_HOOK(bool32);

void Ring_UnconditionalAttract(); //dskfasjudf

void Player_StageLoad_OVERLOAD();
void Player_Create_OVERLOAD(void* data);
void Player_Update_OVERLOAD();

#define OBJ_PLAYER_SETUP \
  IMPORT_PUBLIC_FUNC(Player_GiveScore); \
  IMPORT_PUBLIC_FUNC(Player_GiveRings); \
  IMPORT_PUBLIC_FUNC(Player_SpawnMightyHammerdropDust); \
  IMPORT_PUBLIC_FUNC(Player_CheckCollisionTouch); \
  IMPORT_PUBLIC_FUNC(Player_CheckCollisionPlatform); \
  IMPORT_PUBLIC_FUNC(Player_Gravity_True); \
  IMPORT_PUBLIC_FUNC(Player_HandleAirMovement); \
  IMPORT_PUBLIC_FUNC(Player_HandleAirFriction); \
  IMPORT_PUBLIC_FUNC(Player_State_Air); \
  IMPORT_PUBLIC_FUNC(Player_State_KnuxGlideLeft); \
  IMPORT_PUBLIC_FUNC(Player_State_KnuxGlideRight); \
  IMPORT_PUBLIC_FUNC(Player_State_KnuxWallClimb); \
  IMPORT_PUBLIC_FUNC(Player_Input_P2_AI); \
  IMPORT_PUBLIC_FUNC(Player_State_Static); \
  IMPORT_PUBLIC_FUNC(Player_State_Transform); \
  IMPORT_PUBLIC_FUNC(Player_State_Ground); \
  HOOK_IMPORTED_STATE(Player_State_Ground, 1); \
  HOOK_STATE(Player_JumpAbility_Sonic, 1); \
  HOOK_STATE(Player_JumpAbility_Mighty, 0); \
  HOOK_STATE(Player_State_MightyHammerDrop, 1); \
  HOOK_STATE(Player_State_RayGlide, 1); \
  MOD_REGISTER_OBJ_OVERLOAD(Player, Player_Update_OVERLOAD, NULL, NULL, NULL, Player_Create_OVERLOAD, Player_StageLoad_OVERLOAD, NULL, NULL, NULL)

void Player_BlendHyperPalette(int32 paletteSlot, int32 bankID, const hyperpal_t* info);
bool32 Player_IsHyper(EntityPlayer* player);
void Player_ClearEnemiesOnScreen(EntityPlayer* player);
void Player_HyperSonicDash();
int32 Player_GetIndexFromID(int32 ID);

#endif //! OBJ_PLAYER_H
