#include "Player.h"
#include "Camera.h"
#include "Debris.h"
#include "FXFade.h"
#include "ItemBox.h"
#include "ImageTrail.h"
#include "SuperFlicky.h"
#include "HyperStars.h"
#include "Zone.h"

#include "CPZ/CPZSetup.h"
#include "OOZ/OOZSetup.h"
#include "HCZ/HCZSetup.h"
#include "MMZ/FarPlane.h"

int32 sfxEarthquake;
int32 sfxEarthquake2;

// SYMBOL DEFINITIONS ----------------------------------------------------------
ObjectPlayer* Player;
bool32 (*Player_CheckBadnikBreak)(EntityPlayer*, void*, bool32);
Hitbox* (*Player_GetHitbox)(EntityPlayer* player);
void (*Player_State_Air)(void);
void (*Player_State_KnuxGlideLeft)(void);
void (*Player_State_KnuxGlideRight)(void);
void (*Player_State_KnuxWallClimb)(void);
void (*Player_GiveScore)(EntityPlayer *player, int32 score);
void (*Player_GiveRings)(EntityPlayer *player, int32 amount, bool32 playSfx);
bool32 (*Player_CheckCollisionTouch)(EntityPlayer* player, void* e, Hitbox* entityHitbox);


// PALETTE STUFF ---------------------------------------------------------------
color hyperWhite[3][6] = {
	{ 0xB7CECE, 0xDFF3F3, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF },
	{ 0xB7CECE, 0xDFF3F3, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF },
	{ 0xB7CECE, 0xDFF3F3, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF }
};

color hyperPalette_Sonic[36] = {
	0xF0C001, 0xF0D028, 0xF0E040, 0xF0E860, 0xF0E898, 0xF0E8D0,  // yellow
	0xCC7A8C, 0xE6A0A5, 0xEEB9B6, 0xECCCC9, 0xECD8D3, 0xEFE8E3,  // pink
	0x8A6E90, 0xBE9BC0, 0xD6B4D8, 0xE7C4E6, 0xEED6EB, 0xF9ECF5,  // purple
	0x6877E0, 0x82A1EF, 0x9EC2F9, 0xB4D8FC, 0xC5E3F8, 0xD8F3F3,  // blue
	0x00B354, 0x3CCF5E, 0x64E373, 0x96EF96, 0xBCF3BD, 0xEBF5EA,  // green
	0xAF9600, 0xC7C20E, 0xC4D734, 0xC7E463, 0xD3F296, 0xF7F3F7   // lime yellow
};
color hyperPalette_Tails[6]  = { 0xF03830, 0xF06848, 0xF09860, 0xF0B868, 0xF0C870, 0xF0D870 };
color hyperPalette_Knux[6]   = { 0xF05878, 0xF06090, 0xF080A0, 0xF098B0, 0xF0B0C8, 0xF0C0C8 };
color hyperPalette_Mighty[6] = { 0x701010, 0xD84040, 0xF05858, 0xF07878, 0xF0B8B8, 0xF0E0E8 };
color hyperPalette_Ray[6]    = { 0xE0A801, 0xF0C820, 0xF0E820, 0xF0F040, 0xF0F068, 0xF0F0B8 };
color hyperPalette_Sonic_HCZ[36] = {
	0xF0C001, 0xF0D028, 0xF0E040, 0xF0E860, 0xF0E898, 0xF0E8D0,  // yellow
	0xCC7A8C, 0xE6A0A5, 0xEEB9B6, 0xECCCC9, 0xECD8D3, 0xEFE8E3,  // pink
	0x8A6E90, 0xBE9BC0, 0xD6B4D8, 0xE7C4E6, 0xEED6EB, 0xF9ECF5,  // purple
	0x6877E0, 0x82A1EF, 0x9EC2F9, 0xB4D8FC, 0xC5E3F8, 0xD8F3F3,  // blue
	0x00B354, 0x3CCF5E, 0x64E373, 0x96EF96, 0xBCF3BD, 0xEBF5EA,  // green
	0xAF9600, 0xC7C20E, 0xC4D734, 0xC7E463, 0xD3F296, 0xF7F3F7   // lime yellow
};
color hyperPalette_Tails_HCZ[6]  = { 0xCC6161, 0xDC8462, 0xD5978A, 0xDEA893, 0xE6B09D, 0xEABAA7 };
color hyperPalette_Knux_HCZ[6]   = { 0x746DA3, 0x7F65D0, 0x9768E0, 0xC070EF, 0xD086EB, 0xDE9CED };
color hyperPalette_Mighty_HCZ[6] = { 0x401078, 0x9038C0, 0x9068C0, 0x9890E0, 0xA8C0D8, 0xC0E8F0 };
color hyperPalette_Ray_HCZ[6]    = { 0x80B088, 0x78D090, 0x68F080, 0x50F098, 0x90F0C0, 0xA8F0E0 };
color hyperPalette_Sonic_CPZ[36] = {
	0xF0C001, 0xF0D028, 0xF0E040, 0xF0E860, 0xF0E898, 0xF0E8D0,  // yellow
	0xCC7A8C, 0xE6A0A5, 0xEEB9B6, 0xECCCC9, 0xECD8D3, 0xEFE8E3,  // pink
	0x8A6E90, 0xBE9BC0, 0xD6B4D8, 0xE7C4E6, 0xEED6EB, 0xF9ECF5,  // purple
	0x6877E0, 0x82A1EF, 0x9EC2F9, 0xB4D8FC, 0xC5E3F8, 0xD8F3F3,  // blue
	0x00B354, 0x3CCF5E, 0x64E373, 0x96EF96, 0xBCF3BD, 0xEBF5EA,  // green
	0xAF9600, 0xC7C20E, 0xC4D734, 0xC7E463, 0xD3F296, 0xF7F3F7   // lime yellow
};
color hyperPalette_Tails_CPZ[6]  = { 0xF078F0, 0xF078F0, 0xF080F0, 0xF088F0, 0xF098F0, 0xF0A0F0 };
color hyperPalette_Knux_CPZ[6]   = { 0xF078D8, 0xF078E8, 0xF088F0, 0xF098F0, 0xF0A8F0, 0xF0B0F0 };
color hyperPalette_Mighty_CPZ[6] = { 0xB80180, 0xE001A8, 0xE001C8, 0xE001E0, 0xE040E0, 0xE078E0 };
color hyperPalette_Ray_CPZ[6]    = { 0xE02880, 0xE05888, 0xE08088, 0xE080A8, 0xE080D8, 0xE080E0 };

// ive already spent over a day trying to figure out how to make underwater CPZ/HCZ palettes that dont look like shit and i have better things to work on so for now theyre disabled
// also its kinda inefficient to have members for the normal palettes when i could just access them directly but i wanted to make the paletteInfo structure comprehensive in case i wanted to add custom character support later on
const paletteInfo hyperPaletteInfo[] = {{
		64, 69, 6,
		{
			{ 0x000080, 0x0038C0, 0x0068F0, 0x1888F0, 0x30A0F0, 0x68D0F0 },
			{ 0x200888, 0x3020C8, 0x3840F0, 0x4070F0, 0x4098F0, 0x40C0F0 },
			{ 0x4000D8, 0x5800E0, 0x6810E0, 0x8020E0, 0xA020E0, 0xC040E0 }
		},
		{ hyperPalette_Sonic, hyperPalette_Sonic, hyperPalette_Sonic }
	},{
		70, 75, 1,
		{
			{ 0x800801, 0xB01801, 0xD05001, 0xE07808, 0xE89008, 0xF0A801 },
			{ 0x880808, 0xA03810, 0xA05848, 0xB07058, 0xC08068, 0xC89078 },
			{ 0xC80180, 0xD00178, 0xE00180, 0xE81088, 0xE83098, 0xE84898 }
		},
		{ hyperPalette_Tails, hyperPalette_Tails, hyperPalette_Tails }
	},{
		80, 85, 1,
		{
			{ 0x580818, 0x980130, 0xD00840, 0xE82858, 0xF06080, 0xF08088 },
			{ 0x181050, 0x301090, 0x5018A8, 0x8828C0, 0xA048C0, 0xB868C8 },
			{ 0xA00180, 0xB00178, 0xC00190, 0xD001B0, 0xE001E0, 0xE820E8 }
		},
		{ hyperPalette_Knux, hyperPalette_Knux, hyperPalette_Knux }
	},{
		96, 102, 1,
		{
			{ 0x501010, 0x882020, 0xA83030, 0xC84040, 0xE06868, 0xF09098 },
			{ 0x381058, 0x502098, 0x7028B0, 0x8048C8, 0x7868C8, 0x8098D0 },
			{ 0xA00180, 0xD80188, 0xE001A0, 0xE001B0, 0xE001D8, 0xE001E0 }
		},
		{ hyperPalette_Mighty, hyperPalette_Mighty, hyperPalette_Mighty }
	},{
		113, 119, 1,
		{
			{ 0xA06800, 0xB88810, 0xD0A810, 0xE0C020, 0xE8D038, 0xF0E078 },
			{ 0x406090, 0x488890, 0x68A880, 0x70C080, 0x68D080, 0x50E888 },
			{ 0xE00180, 0xE00190, 0xE02898, 0xE048A8, 0xE060B8, 0xE078E0 }
		},
		{ hyperPalette_Ray, hyperPalette_Ray, hyperPalette_Ray }
}};


// EXTRA MEMBER VARIABLES ------------------------------------------------------
hyper_t hyperInstance[PLAYER_COUNT];


// FUNCTIONS -------------------------------------------------------------------
void Player_StageLoad_Hook(void) {
	Mod.Super(Player->classID, SUPER_STAGELOAD, NULL);
	sfxEarthquake = RSDK.GetSfx("Stage/Impact5.wav");
	sfxEarthquake2 = RSDK.GetSfx("Stage/Impact2.wav");
}

void Player_Draw_Hook(void) {
	Mod.Super(Player->classID, SUPER_DRAW, NULL);
	RSDK_THIS(Player);

	if (Player_IsHyper(self)) {
		int32 old_alpha = self->alpha;
		InkEffects old_ink = self->inkEffect;
		self->alpha = self->superBlendAmount / 2;
		self->inkEffect = INK_SUB;
		RSDK.DrawSprite(&self->animator, NULL, false);
		self->alpha /= 1.5;
		self->inkEffect = INK_ADD;
		RSDK.DrawSprite(&self->animator, NULL, false);
		self->alpha = old_alpha;
		self->inkEffect = old_ink;
	}
}

void Player_Update_Hook(void) {
	RSDK_THIS(Player);

	hyper_t* ext = &hyperInstance[RSDK.GetEntitySlot(self)];
	ext->prev_ID = self->characterID;
	ext->prev_xvel = self->velocity.x;
	void* prev_state = self->state;
	Mod.Super(Player->classID, SUPER_UPDATE, NULL);

	if (self->superState == SUPERSTATE_NONE) {
		ext->is_hyper = false;
		Music_SetMusicTrack("Super.ogg", 10, 165375);
		return;
	}

	// hyper transformation ------------------------------------------------
	RSDKControllerState* controller = &ControllerInfo[self->controllerID];
	if (!ext->is_hyper && controller->keyZ.press && localHM_SaveRam.superEmeralds == 0b01111111) {
		ext->blend.state = -1;
		ext->blend.amount = 0;
		ext->is_hyper = true;
		ext->can_dash = true; // this was added solely to replicate the dashing out of transform thing from S3&K

		Music_SetMusicTrack("Hyper.ogg", 10, 423801);
		Music_PlayJingle(10); // TODO add "is super track playing?" check so it doesnt fuck with ERZ
		RSDK.PlaySfx(Player->sfxRelease, false, 0xFF);
		RSDK.PlaySfx(RSDK.GetSfx("Global/Twinkle.wav"), false, 0xFF); // TODO not good
		if (FXFade) {
			EntityFXFade* fade = CREATE_ENTITY(FXFade, INT_TO_VOID(0xF0F0F0), self->position.x, self->position.y);
			fade->speedIn = 0x100;
			fade->speedOut = 0x10;
		}
	}
	if (!ext->is_hyper) return;

	// encore shit ---------------------------------------------------------
	if (ext->prev_ID != self->characterID) {
		EntityPlayer* sidekick = RSDK_GET_ENTITY(SLOT_PLAYER2, Player);
		if (sidekick->classID && ext->prev_ID == sidekick->characterID) {
			hyperInstance[RSDK.GetEntitySlot(sidekick)].is_hyper = true;
			hyperInstance[RSDK.GetEntitySlot(sidekick)].blend.amount = ext->blend.amount;
			hyperInstance[RSDK.GetEntitySlot(sidekick)].blend.state = ext->blend.state;
		}
		ext->blend.state = -1;
		ext->blend.amount = 0;
	}

	// palette shifting ----------------------------------------------------
	int32 index = -1;
	switch (self->characterID) {
		case ID_SONIC:    index = 0; break;
		case ID_TAILS:    index = 1; break;
		case ID_KNUCKLES: index = 2; break;
		case ID_MIGHTY:   index = 3; break;
		case ID_RAY:      index = 4; break;
	}
	if (index != -1) {
		const paletteInfo* info = &hyperPaletteInfo[index];

		if (ext->blend.amount >= 0x100) {
			if (self->superState == SUPERSTATE_SUPER || self->superBlendState != 1) {
				ext->blend.amount = 0;
				ext->blend.state = (ext->blend.state + 1) % (info->rows * 2);
			}
		} else {
			ext->blend.amount += (ext->blend.state < 0) ? 8
			                                            : 16 + 24 * (ext->blend.state & 1);
		}

		// paletteSlot and bankID are usually the same value but theyre seperate arguments just in case
		if (HCZSetup) {
			Player_BlendHyperPalette(1, 1, info);
		} else if (CPZSetup) {
			Player_BlendHyperPalette(2, 2, info);
		}
		Player_BlendHyperPalette(0, 0, info);
		if (FarPlane) {
			RSDK.CopyPalette(0, info->startIndex, 3, info->startIndex, 6);
		} else if (OOZSetup) {
			RSDK.CopyPalette(0, info->startIndex, 1, info->startIndex, 6);
			RSDK.CopyPalette(0, info->startIndex, 2, info->startIndex, 6);
		}
	}

	// extra abilities -----------------------------------------------------
	if (self->superState == SUPERSTATE_SUPER) {
		self->drownTimer = 0;

		if (self->characterID == ID_SONIC && ext->can_dash && self->velocity.y >= 0 && self->jumpPress) {
			Player_HyperSonicDash();
			ext->can_dash = false;
		}

		Entity* entity = RSDK_GET_ENTITY_GEN(self->playerID + Player->playerCount);
		if (entity->classID != HyperStars->classID) RSDK.ResetEntity(entity, HyperStars->classID, self);
		if (self->characterID == ID_TAILS) {
			entity = RSDK_GET_ENTITY_GEN(SuperFlickySlot);
			if (entity->classID != SuperFlicky->classID) RSDK.ResetEntity(entity, SuperFlicky->classID, self);
		}
		if ((void*)self->state == (void*)Player_State_KnuxGlideLeft || (void*)self->state == (void*)Player_State_KnuxGlideRight) {
			// gliding momentum retention
			if (prev_state != (void*)Player_State_KnuxGlideLeft && prev_state != (void*)Player_State_KnuxGlideRight) {
				if (self->velocity.x > 0 && ext->prev_xvel > self->velocity.x) self->velocity.x = ext->prev_xvel;
				if (self->velocity.x < 0 && ext->prev_xvel < self->velocity.x) self->velocity.x = ext->prev_xvel;
				self->abilitySpeed = self->velocity.x / RSDK.Cos512(self->timer) << 9;
			}

			// earthquake
			if (abs(ext->prev_xvel) >= 0x48000 && self->velocity.x == 0 && self->abilitySpeed != 0) {
				Player_ClearEnemiesOnScreen(self);
				Camera_ShakeScreen(RSDK.GetEntitySlot(self), 6, 0);
				RSDK.StopSfx(Player->sfxGrab);
				RSDK.PlaySfx(sfxEarthquake, false, 0xFF);
				RSDK.SetChannelAttributes(RSDK.PlaySfx(sfxEarthquake2, false, 0xFF), 0.6, 0.0, 1.0);
				foreach_all(ItemBox, box) {
					if (RSDK.CheckOnScreen(box, NULL) && (void*)box->state != (void*)ItemBox_State_Broken) {
						ItemBox_Break(box, self);
					}
				}
			}
		}

	}
}

bool32 Player_JumpAbility_Sonic_Hook(bool32 skippedState) {
	RSDK_THIS(Player);
	if (!Player_IsHyper(self)) return false;
	hyper_t* ext = &hyperInstance[RSDK.GetEntitySlot(self)];

	if (self->jumpAbilityState == 1 && self->jumpPress) {
		Player_HyperSonicDash();
	}
	ext->can_dash = false;
	return false;
}

void Player_HyperSonicDash() {
	RSDK_THIS(Player);
	Player_ClearEnemiesOnScreen(self);

	if (globals->medalMods & MEDAL_NODROPDASH) self->jumpAbilityState = 0;
	else self->jumpAbilityState = 22; // naughty naughty
	if (!(self->up || self->down || self->left || self->right)) {
		self->velocity.x = 0x80000 * (self->direction ? -1 : 1);
		self->velocity.y = 0;
	} else {
		self->velocity.x = 0x80000 * (self->right - self->left);
		self->velocity.y = 0x80000 * (self->down - self->up);
	}

	RSDK.SetChannelAttributes(RSDK.PlaySfx(Player->sfxRelease, false, 0xFF), 1.1, 0.0, 1.0);
	RSDK.SetChannelAttributes(RSDK.PlaySfx(ItemBox->sfxHyperRing, false, 0xFF), 0.4, 0.0, 1.0);
	EntityCamera* camera = self->camera;
	if (camera && !Zone->autoScrollSpeed) {
		self->scrollDelay = 15;
		camera->state     = Camera_State_FollowY;
	}

	if (FXFade) {
		EntityFXFade* fade = CREATE_ENTITY(FXFade, INT_TO_VOID(0xF0F0F0), self->position.x, self->position.y);
		fade->timer = 0x200;
		fade->speedOut = 0x30;
		fade->state = FXFade_State_FadeIn;
	}

	const int32 vel = 0x2C000;
	for (int32 i = 0; i != 4; ++i) {
		EntityDebris* debris = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
		debris->timer = 13;
		debris->velocity.x = vel - vel * (2 * (i & 1));
		debris->velocity.y = vel - vel * (i & 2);
		debris->drawGroup = Zone->playerDrawGroup[1];
		RSDK.SetSpriteAnimation(HyperStars->aniFrames, 0, &debris->animator, true, 0);
		if (self->drawFX & FX_SCALE) {
			debris->drawFX |= FX_SCALE;
			debris->scale.x = self->scale.x;
			debris->scale.y = self->scale.y;
		}
	}
}

bool32 Player_State_KnuxGlide_Hook(bool32 skippedState) {
	return false;
}

void Player_BlendHyperPalette(int32 paletteSlot, int32 bankID, const paletteInfo* info) {
	RSDK_THIS(Player);
	const hyper_t* ext = &hyperInstance[RSDK.GetEntitySlot(self)];
	const color* palette = info->hyper_colors[paletteSlot];

	if (ext->blend.state < 0) {
		for (int32 i = 0; i < 6; ++i) {
			RSDK.SetPaletteEntry(7, i + info->startIndex, hyperWhite[paletteSlot][i]);
			RSDK.SetPaletteEntry(6, i + info->startIndex, info->normal_colors[paletteSlot][i]);
		}
		RSDK.SetLimitedFade(bankID, 6, 7, ext->blend.amount, info->startIndex, info->endIndex);
	} else {
		for (int32 i = 0; i < 6; ++i) {
			if (ext->blend.state & 1) {
				// color -> white
				RSDK.SetPaletteEntry(6, i + info->startIndex, palette[i + (int32)(ext->blend.state / 2) * 6]);
				RSDK.SetPaletteEntry(7, i + info->startIndex, hyperWhite[paletteSlot][i]);
			} else {
				// white -> color
				RSDK.SetPaletteEntry(6, i + info->startIndex, hyperWhite[paletteSlot][i]);
				RSDK.SetPaletteEntry(7, i + info->startIndex, palette[i + (int32)(ext->blend.state / 2) * 6]);
			}
		}

		RSDK.SetLimitedFade(bankID, 6, 7, ext->blend.amount, info->startIndex, info->endIndex);
		if (self->superState != SUPERSTATE_SUPER) {
			for (int32 i = 0; i < 6; ++i) {
				RSDK.SetPaletteEntry(6, i + info->startIndex, info->normal_colors[paletteSlot][i]);
			}
			RSDK.SetLimitedFade(bankID, 6, bankID, self->superBlendAmount, info->startIndex, info->endIndex);
		}
	}
}

bool32 Player_IsHyper(EntityPlayer* player) {
	return (player->superState == SUPERSTATE_SUPER && hyperInstance[RSDK.GetEntitySlot(player)].is_hyper);
}

void Player_ClearEnemiesOnScreen(EntityPlayer* player) {
	for (int16 i = 0; i != ENTITY_COUNT; ++i) {
		Entity* entity = RSDK_GET_ENTITY_GEN(i);
		if (!entity->classID || !IsVulnerableEnemy(entity, false) || !IsEnemyOnScreen(entity)) continue;
		HitEnemy(player, entity);
	}
}
