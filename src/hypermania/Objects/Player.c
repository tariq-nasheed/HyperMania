#include "Player.h"
#include "Camera.h"
#include "Debris.h"
#include "FXFade.h"
#include "Ring.h"
#include "ItemBox.h"
#include "ImageTrail.h"
#include "SuperFlicky.h"
#include "HyperStars.h"
#include "Zone.h"

#include "CPZ/CPZSetup.h"
#include "OOZ/OOZSetup.h"
#include "HCZ/HCZSetup.h"
#include "MMZ/FarPlane.h"
#include "ERZ/ERZStart.h"


// -----------------------------------------------------------------------------
ObjectPlayer* Player;
void (*Player_State_Air)(void);
void (*Player_State_KnuxGlideLeft)(void);
void (*Player_State_KnuxGlideRight)(void);
void (*Player_State_KnuxWallClimb)(void);
void (*Player_Input_P2_AI)();
void (*Player_GiveScore)(EntityPlayer *player, int32 score);
void (*Player_GiveRings)(EntityPlayer *player, int32 amount, bool32 playSfx);
bool32 (*Player_CheckCollisionTouch)(EntityPlayer* player, void* e, Hitbox* entityHitbox);

// -----------------------------------------------------------------------------
static bool32 (*formerCanSuperCB)(bool32);
static bool32 disableSuperPostTransfer(bool32 isHUD) {
	if (formerCanSuperCB && formerCanSuperCB(isHUD) == false) return false;
	if (!ERZStart && HM_global.currentSave->transferedEmeralds && HM_global.currentSave->superEmeralds != 0b01111111) {
		return false;
	}
	return true;
}

// -----------------------------------------------------------------------------
PlayerStaticExt_t PlayerStaticExt;

// C doesn't let you initialize arrays inside of anonymous structs so i have to do this instead of putting it in PlayerStaticExt
static color hyperPalette_Sonic[36] = {
	0xF0C001, 0xF0D028, 0xF0E040, 0xF0E860, 0xF0E898, 0xF0E8D0,  // yellow (TODO make seperate from mania super sonic yellow)
	0xCC7A8C, 0xE6A0A5, 0xEEB9B6, 0xECCCC9, 0xECD8D3, 0xEFE8E3,  // pink
	0x8A6E90, 0xBE9BC0, 0xD6B4D8, 0xE7C4E6, 0xEED6EB, 0xF9ECF5,  // purple
	0x6877E0, 0x82A1EF, 0x9EC2F9, 0xB4D8FC, 0xC5E3F8, 0xD8F3F3,  // blue
	0x00B354, 0x3CCF5E, 0x64E373, 0x96EF96, 0xBCF3BD, 0xEBF5EA,  // green
	0xAF9600, 0xC7C20E, 0xC4D734, 0xC7E463, 0xD3F296, 0xF7F3F7   // lime yellow
};

color PlayerPaletteWhite[3][6] = {
	{ 0xB7CECE, 0xDFF3F3, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF },
	{ 0xB7CECE, 0xDFF3F3, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF },
	{ 0xB7CECE, 0xDFF3F3, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF }
};

hyperpal_t PlayerPaletteDefs[] = {
	{ 64,  69,  6, { hyperPalette_Sonic, hyperPalette_Sonic, hyperPalette_Sonic, NULL, NULL, NULL } },
	{ 70,  75,  1, { NULL, NULL, NULL, NULL, NULL, NULL } },
	{ 80,  85,  1, { NULL, NULL, NULL, NULL, NULL, NULL } },
#if MANIA_USE_PLUS
	{ 96,  102, 1, { NULL, NULL, NULL, NULL, NULL, NULL } },
	{ 113, 119, 1, { NULL, NULL, NULL, NULL, NULL, NULL } },
#endif
};


// -----------------------------------------------------------------------------
void Player_StageLoad_OVERLOAD() {
	Mod.Super(Player->classID, SUPER_STAGELOAD, NULL);

	// hyperpal_t.colors layout
	// ===== used for palette animation while hyper =====
	//  0 -- pointer to normal hyper palette
	//  1 -- pointer to HCZ hyper palette
	//  2 -- pointer to CPZ hyper palette
	// ===== used for detransformation palette animation =====
	//  3 -- pointer to normal default palette
	//  4 -- pointer to HCZ normal palette
	//  5 -- pointer to CPZ normal palette

	PlayerPaletteDefs[0].colors[3] = &Player->superPalette_Sonic[0];
	PlayerPaletteDefs[0].colors[4] = &Player->superPalette_Sonic_HCZ[0];
	PlayerPaletteDefs[0].colors[5] = &Player->superPalette_Sonic_CPZ[0];

	// every non-sonic character resuses the brighter oscillation of their super palette
	PlayerPaletteDefs[1].colors[0] = &Player->superPalette_Tails[6];
	PlayerPaletteDefs[1].colors[1] = &Player->superPalette_Tails_HCZ[6];
	PlayerPaletteDefs[1].colors[2] = &Player->superPalette_Tails_CPZ[6];
	PlayerPaletteDefs[1].colors[3] = &Player->superPalette_Tails[0];
	PlayerPaletteDefs[1].colors[4] = &Player->superPalette_Tails_HCZ[0];
	PlayerPaletteDefs[1].colors[5] = &Player->superPalette_Tails_CPZ[0];

	PlayerPaletteDefs[2].colors[0] = &Player->superPalette_Knux[6];
	PlayerPaletteDefs[2].colors[1] = &Player->superPalette_Knux_HCZ[6];
	PlayerPaletteDefs[2].colors[2] = &Player->superPalette_Knux_CPZ[6];
	PlayerPaletteDefs[2].colors[3] = &Player->superPalette_Knux[0];
	PlayerPaletteDefs[2].colors[4] = &Player->superPalette_Knux_HCZ[0];
	PlayerPaletteDefs[2].colors[5] = &Player->superPalette_Knux_CPZ[0];
#if MANIA_USE_PLUS
	PlayerPaletteDefs[3].colors[0] = &Player->superPalette_Mighty[6];
	PlayerPaletteDefs[3].colors[1] = &Player->superPalette_Mighty_HCZ[6];
	PlayerPaletteDefs[3].colors[2] = &Player->superPalette_Mighty_CPZ[6];
	PlayerPaletteDefs[3].colors[3] = &Player->superPalette_Mighty[0];
	PlayerPaletteDefs[3].colors[4] = &Player->superPalette_Mighty_HCZ[0];
	PlayerPaletteDefs[3].colors[5] = &Player->superPalette_Mighty_CPZ[0];

	PlayerPaletteDefs[4].colors[0] = &Player->superPalette_Ray[6];
	PlayerPaletteDefs[4].colors[1] = &Player->superPalette_Ray_HCZ[6];
	PlayerPaletteDefs[4].colors[2] = &Player->superPalette_Ray_CPZ[6];
	PlayerPaletteDefs[4].colors[3] = &Player->superPalette_Ray[6];
	PlayerPaletteDefs[4].colors[4] = &Player->superPalette_Ray_HCZ[6];
	PlayerPaletteDefs[4].colors[5] = &Player->superPalette_Ray_CPZ[6];
#endif

	PlayerStaticExt.sfxEarthquake = RSDK.GetSfx("Stage/Impact5.wav");
	PlayerStaticExt.sfxEarthquake2 = RSDK.GetSfx("Stage/Impact2.wav");
}

void Player_Draw_OVERLOAD() {
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

void Player_Create_OVERLOAD(void* data) {
	Mod.Super(Player->classID, SUPER_CREATE, data);
	RSDK_THIS(Player);

	PlayerExt* ext = (PlayerExt*)AllocExtMem(RSDK.GetEntitySlot(self), sizeof(PlayerExt));
}

void Player_Update_OVERLOAD() {
	RSDK_THIS(Player);

	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));
	ext->prev_ID = self->characterID;
	ext->prev_xvel = self->velocity.x;
	void* prev_state = self->state;

	formerCanSuperCB = Player->canSuperCB;
	Player->canSuperCB = disableSuperPostTransfer;
	Mod.Super(Player->classID, SUPER_UPDATE, NULL);
	if (Player->canSuperCB == disableSuperPostTransfer) {
		Player->canSuperCB = formerCanSuperCB;
	}

	if (prev_state != self->state) {
		ext->prev_state = prev_state;
	}

	if (self->superState == SUPERSTATE_NONE) {
		ext->is_hyper = false;
		return;
	}

	// hyper transformation ------------------------------------------------
	RSDKControllerState* controller = &ControllerInfo[self->controllerID];
	if (!ext->is_hyper && (controller->keyZ.press || HM_global.currentSave->superEmeralds == 0b01111111)) {
		if (!ERZStart) Music_SetMusicTrack("Hyper.ogg", TRACK_SUPER, 423801);
		ext->blend.state = HYPERBLEND_FADEIN;
		ext->blend.amount = 0;
		ext->is_hyper = true;
		ext->can_dash = true; // this was added solely to replicate the dashing out of transform thing from S3&K

		if (controller->keyZ.press) {
			RSDK.PlaySfx(Player->sfxRelease, false, 0xFF);
			RSDK.PlaySfx(RSDK.GetSfx("Global/Twinkle.wav"), false, 0xFF); // TODO not good
			if (FXFade) {
				EntityFXFade* fade = CREATE_ENTITY(FXFade, INT_TO_VOID(0xF0F0F0), self->position.x, self->position.y);
				fade->speedIn = 0x100;
				fade->speedOut = 0x10;
			}
		}
	}
	if (!ext->is_hyper) return;

	// encore shit ---------------------------------------------------------
#if MANIA_USE_PLUS
	if (ext->prev_ID != self->characterID) {
		PlayerExt* sidekick_ext = (PlayerExt*)GetExtMem(SLOT_PLAYER2);
		if (sidekick_ext && ext->prev_ID == RSDK_GET_ENTITY(SLOT_PLAYER2, Player)->characterID) {
			printf("player swap\n");
			sidekick_ext->is_hyper = true;
			sidekick_ext->blend.amount = ext->blend.amount;
			sidekick_ext->blend.state = ext->blend.state;
		}
		ext->blend.state = HYPERBLEND_FADEIN;
		ext->blend.amount = 0;
	}
#endif

	// palette shifting ----------------------------------------------------
	int32 index = Player_GetIndexFromID(self->characterID);

	if (index != -1) {
		const hyperpal_t* info = &PlayerPaletteDefs[index];

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
				RSDK.PlaySfx(PlayerStaticExt.sfxEarthquake, false, 0xFF);
				RSDK.SetChannelAttributes(RSDK.PlaySfx(PlayerStaticExt.sfxEarthquake2, false, 0xFF), 0.6, 0.0, 1.0);
				foreach_all(ItemBox, box) {
					if (RSDK.CheckOnScreen(box, NULL) && (void*)box->state != (void*)ItemBox_State_Broken) {
						ItemBox_Break(box, self);
					}
				}
			}
		}
	}

	// music handling ------------------------------------------------------
	if (!ERZStart && Music->activeTrack == TRACK_SUPER && Music->trackLoops[TRACK_SUPER] != 423801) {
#if MANIA_USE_PLUS
		Music_JingleFadeOut(TRACK_SUPER, false);
		Music_PlayJingle(TRACK_SUPER);
#else
		Music_TransitionTrack(TRACK_HYPER, 1.0);
#endif
	}
}

bool32 Player_State_Transform_HOOK(bool32 skippedState) {
	/*RSDK_THIS(Player);
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));

	if (!ERZStart && HM_global.currentSave->transferedEmeralds && HM_global.currentSave->superEmeralds != 0b01111111) {
		printf("collect all super emeralds >:(\n");
		self->state = ext->prev_state;
#if GAME_VERSION != VER_100
		self->isTransforming = false;
#endif
		self->interaction = true;
		return true;
	}*/
	return false;
}


bool32 Player_State_Ground_HOOK(bool32 skippedState) {
	RSDK_THIS(Player);
	if (!Player_IsHyper(self)) return false;
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));
	if (self->characterID == ID_MIGHTY) ext->can_dash = true;
	return false;
}

bool32 Player_JumpAbility_Sonic_HOOK(bool32 skippedState) {
	RSDK_THIS(Player);
	if (!Player_IsHyper(self)) return false;
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));

	if (self->jumpAbilityState == 1 && self->jumpPress) {
		Player_HyperSonicDash();
	}
	ext->can_dash = false;
	return false;
}

bool32 Player_JumpAbility_Mighty_HOOK(bool32 skippedState) {
	if (skippedState) return true;
	RSDK_THIS(Player);
	if (!Player_IsHyper(self)) return false;
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));
	if (!ext->can_dash) return false;

	if (!self->invertGravity
	&& self->jumpPress && self->jumpAbilityState == 0
	&& (self->stateInput != Player_Input_P2_AI || (self->up && globals->gameMode != MODE_ENCORE))) {
		self->velocity.y *= 2;
		RSDK.StopSfx(Player->sfxRelease);
		RSDK.PlaySfx(Player->sfxPeelRelease, false, 0xFF);
	}
	return false;
}

bool32 Player_State_MightyHammerDrop_HOOK(bool32 skippedState) {
	if (skippedState) return true;
	RSDK_THIS(Player);
	if (!Player_IsHyper(self)) return false;
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));

	if (self->jumpAbilityState == 3) {
		if (ext->can_dash) {
			ext->can_dash = false;
			Camera_ShakeScreen(RSDK.GetEntitySlot(self), 4, 12);
			RSDK.PlaySfx(PlayerStaticExt.sfxEarthquake, false, 0xFF);
			int32 dropForce = self->gravityStrength + (self->underwater == 1 ? 0x10000 : 0x20000);
			int32 groundVel = self->groundVel - (self->groundVel >> 2);

			/*self->velocity.x = ((groundVel * RSDK.Cos256(self->angle) + dropForce * RSDK.Sin256(self->angle)) >> 8);// * 3.5;
			self->velocity.y = ((groundVel * RSDK.Sin256(self->angle) - dropForce * RSDK.Cos256(self->angle)) >> 8);// * 3.5;*/
			self->velocity.x *= 3;
			self->velocity.y *= 3;
			foreach_all(Ring, ring) {
				if (((ring->position.y + TO_FIXED(8) > self->position.y - TO_FIXED(512) && ring->position.x > self->position.x - TO_FIXED(256) && ring->position.x < self->position.x + TO_FIXED(256))
				    || RSDK.CheckObjectCollisionTouchCircle(self, TO_FIXED(256), ring, TO_FIXED(16)))
				&& !ring->storedPlayer && ring->state != Ring_State_Sparkle && ring->state != Ring_State_Lost) {
					ring->state = Ring_State_Lost;
					ring->timer = 0x3F + 1;
					ring->velocity.x = RSDK.Rand(-0x20000, 0x20000);// + CLAMP(self->position.x - ring->position.x, -0x20000, 0x20000);
					ring->velocity.y = RSDK.Rand(-0x5000, 0x50000);
					ring->animator.speed = 0x200;
					ring->active = ACTIVE_NORMAL;
				}
			}
			Player_ClearEnemiesOnScreen(self);
			EntityFXFade* fade = CREATE_ENTITY(FXFade, INT_TO_VOID(0xF0F0F0), self->position.x, self->position.y);
			fade->timer = 0x180;
			fade->speedOut = 0x18;
			fade->state = FXFade_State_FadeIn;
		} else {
			self->velocity.x *= 2;
			self->velocity.y *= 2;
		}
		self->jumpAbilityState = 1;
	}
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

	EntityFXFade* fade = CREATE_ENTITY(FXFade, INT_TO_VOID(0xF0F0F0), self->position.x, self->position.y);
	fade->timer = 0x200;
	fade->speedOut = 0x30;
	fade->state = FXFade_State_FadeIn;

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

void Player_BlendHyperPalette(int32 paletteSlot, int32 bankID, const hyperpal_t* info) {
	RSDK_THIS(Player);
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));
	const color* palette = info->colors[paletteSlot];

	if (ext->blend.state == HYPERBLEND_FADEIN) {
		for (int32 i = 0; i < 6; ++i) {
			RSDK.SetPaletteEntry(7, i + info->startIndex, PlayerPaletteWhite[paletteSlot][i]);
		}
		RSDK.SetLimitedFade(bankID, 6, 7, ext->blend.amount, info->startIndex, info->endIndex);
	} else {
		for (int32 i = 0; i < 6; ++i) {
			RSDK.SetPaletteEntry(6, i + info->startIndex, palette[i + (ext->blend.state >> 1) * 6]);
			RSDK.SetPaletteEntry(7, i + info->startIndex, PlayerPaletteWhite[paletteSlot][i]);
		}
		// 6->7 if on odd blend.state, otherwise 7->6
		RSDK.SetLimitedFade(bankID, 7 - (ext->blend.state & 1), 6 + (ext->blend.state & 1), ext->blend.amount, info->startIndex, info->endIndex);

		if (self->superState != SUPERSTATE_SUPER) {
			for (int32 i = 0; i < 6; ++i) {
				RSDK.SetPaletteEntry(6, i + info->startIndex, info->colors[3 + paletteSlot][i]);
			}
			RSDK.SetLimitedFade(bankID, 6, bankID, self->superBlendAmount, info->startIndex, info->endIndex);
		}
	}
}

bool32 Player_IsHyper(EntityPlayer* player) {
	return (player->superState == SUPERSTATE_SUPER && ((PlayerExt*)GetExtMem(RSDK.GetEntitySlot(player)))->is_hyper);
}

int32 Player_GetIndexFromID(int32 ID) {
	int32 index = -1;
	switch (ID) {
		case ID_SONIC:    index = 0; break;
		case ID_TAILS:    index = 1; break;
		case ID_KNUCKLES: index = 2; break;
#if MANIA_USE_PLUS
		case ID_MIGHTY:   index = 3; break;
		case ID_RAY:      index = 4; break;
#endif
	}
	return index;
}

void Player_ClearEnemiesOnScreen(EntityPlayer* player) {
	for (int16 i = 0; i != ENTITY_COUNT; ++i) {
		Entity* entity = RSDK_GET_ENTITY_GEN(i);
		if (!entity->classID || !IsVulnerableEnemy(entity, false) || !IsEnemyOnScreen(entity)) continue;
		HitEnemy(player, entity);
	}
}