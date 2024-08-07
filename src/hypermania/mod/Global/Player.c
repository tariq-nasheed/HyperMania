#include "Player.h"


// -----------------------------------------------------------------------------
ObjectPlayer* Player;
void (*Player_Gravity_True)();
void (*Player_HandleAirMovement)();
void (*Player_HandleAirFriction)();
void (*Player_State_Air)(void);
void (*Player_State_KnuxGlideLeft)(void);
void (*Player_State_KnuxGlideRight)(void);
void (*Player_State_KnuxWallClimb)(void);
void (*Player_Input_P2_AI)();
void (*Player_GiveScore)(EntityPlayer *player, int32 score);
void (*Player_GiveRings)(EntityPlayer *player, int32 amount, bool32 playSfx);
void (*Player_SpawnMightyHammerdropDust)(int32 speed, Hitbox *hitbox);
void (*Player_State_Static)();
void (*Player_State_Transform)();
void (*Player_State_Ground)();
bool32 (*Player_CheckCollisionTouch)(EntityPlayer* player, void* e, Hitbox* entityHitbox);
bool32 (*Player_CheckCollisionPlatform)(EntityPlayer *player, void *entity, Hitbox *entityHitbox);

// -----------------------------------------------------------------------------
static bool32 (*formerCanSuperCB)(bool32);
static bool32 disableSuperPostTransfer(bool32 isHUD) {
	RSDK_THIS(Player);

	if (formerCanSuperCB && formerCanSuperCB(isHUD) == false) return false;
	if (!ERZStart
	&& (HM_globals->currentSave->transferedEmeralds || (HM_globals->config.superTailsOnly && self->characterID == ID_TAILS))
	&& HM_globals->currentSave->superEmeralds != 0b01111111) {
		return false;
	}
	return true;
}

// -----------------------------------------------------------------------------
PlayerStaticExt_t PlayerStaticExt;

// C doesn't let you initialize arrays inside of anonymous structs so i have to do this instead of putting it in PlayerStaticExt
static color hyperPalette_Sonic[36] = {
	0xF0BD12, 0xEFD445, 0xF5EA5A, 0xF4F09E, 0xF5F5B9, 0xECECD9,  // yellow
	0xF58DA2, 0xF3ADB0, 0xF3C7C4, 0xF3D6D2, 0xF3E6E2, 0xF3F5F5,  // pink
	0xB873CC, 0xC79DCE, 0xD5BDD5, 0xE2CADE, 0xE7E1E5, 0xF2F0F1,  // purple
	0x8393F6, 0x8FAEF6, 0xAFCBF6, 0xC1D8F6, 0xD2E4F6, 0xF3F5F6,  // blue
	0x00D15A, 0x17E066, 0x6FE295, 0xA3E2A8, 0xD3E5CF, 0xE7E7E7,  // green
	0xCCC11C, 0xD9D551, 0xDEE384, 0xDDE3A4, 0xDDEABA, 0xE4EAD3   // lime yellow
};

static color hyperPalette_Sonic_HCZ[36] = {
	0xB4D278, 0xB0DF91, 0xB4E89D, 0xB4ECBE, 0xB4EECF, 0xB0EADF,  // yellow
	0xB4BAC3, 0xB4CACB, 0xB4D7D3, 0xB4DFDB, 0xB4E7E3, 0xB4EEEB,  // pink
	0x97ACD7, 0x9CC2D7, 0xA4D2DB, 0xACD9DF, 0xACE5E3, 0xB4ECEB,  // purple
	0x7BBCEB, 0x7FCAEB, 0x8FD9EB, 0x9CE1EB, 0xA4E7EB, 0xB4EEEB,  // blue
	0x39DD9D, 0x41E5A2, 0x6FE5BA, 0x8BE5C7, 0xA4E7D7, 0xACE7E3,  // green
	0xA0D57C, 0xA8DF99, 0xA8E5B2, 0xA8E5C3, 0xA8E8CF, 0xACE8DB   // lime yellow
};

static color hyperPalette_Sonic_CPZ[36] = {
	0xF27085, 0xEF7C9E, 0xF286AA, 0xF28ACB, 0xF28CDC, 0xEF88EC,  // yellow
	0xF258D0, 0xF268D8, 0xF274E0, 0xF27CE8, 0xF284F1, 0xF28CF9,  // pink
	0xD649E4, 0xDA60E4, 0xE270E8, 0xEB76EC, 0xEB82F1, 0xF28AF9,  // purple
	0xB95AF9, 0xBD68F9, 0xCE76F9, 0xDA7EF9, 0xE284F9, 0xF28CF9,  // blue
	0x777AAA, 0x7F82AF, 0xAD82C7, 0xCA82D4, 0xE284E4, 0xEB84F1,  // green
	0xDE7289, 0xE67CA6, 0xE682BF, 0xE682D0, 0xE686DC, 0xEB86E8   // lime yellow
};
color PlayerPaletteWhite[3][6] = {
	{ 0xEAEAEA, 0xF1F1F1, 0xF8F8F8, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF },
	{ 0xAEE8E5, 0xB1EBE8, 0xB5EFEC, 0xB8F2EF, 0xB8F2EF, 0xB8F2EF },
	{ 0xEC86F2, 0xEF89F6, 0xF38DF9, 0xF690FC, 0xF690FC, 0xF690FC }
};

hyperpal_t PlayerPaletteDefs[] = {
	{ 64,  69,  6, { hyperPalette_Sonic, hyperPalette_Sonic_HCZ, hyperPalette_Sonic_CPZ, NULL, NULL, NULL } },
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

	PlayerStaticExt.shockwaveFrames = RSDK.LoadSpriteAnimation("Global/Shockwave.bin", SCOPE_STAGE);
	PlayerStaticExt.sfxEarthquake = RSDK.GetSfx("Stage/Impact5.wav");
	PlayerStaticExt.sfxEarthquake2 = RSDK.GetSfx("Stage/Impact2.wav");
	PlayerStaticExt.sfxJetGlide = RSDK.GetSfx("Global/JetGlide.wav");
}

void Player_Create_OVERLOAD(void* data) {
	Mod.Super(Player->classID, SUPER_CREATE, data);
	RSDK_THIS(Player);

	AllocExtMem(RSDK.GetEntitySlot(self), sizeof(PlayerExt));
}

void Player_Update_OVERLOAD() {
	RSDK_THIS(Player);

	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));
	if (ext) {
		ext->prev_ID = self->characterID;
		ext->prev_xvel = self->velocity.x;
		ext->prev_state = self->state;
	}

#if MANIA_USE_PLUS
	formerCanSuperCB = Player->canSuperCB;
	Player->canSuperCB = disableSuperPostTransfer;
#endif
	Mod.Super(Player->classID, SUPER_UPDATE, NULL);
#if MANIA_USE_PLUS
	if (Player->canSuperCB == disableSuperPostTransfer) {
		Player->canSuperCB = formerCanSuperCB;
	}
#endif

	if (!ext) return;
	if (self->superState == SUPERSTATE_NONE) {
		ext->is_hyper = false;
		return;
	}

	// hyper transformation ------------------------------------------------
	RSDKControllerState* controller = &ControllerInfo[self->controllerID];
	if (!ext->is_hyper
	&& (HM_globals->currentSave->superEmeralds == 0b01111111 || SceneInfo->debugMode)
	&& ((!HM_globals->config.twoHeavensMode && HM_globals->currentSave->superEmeralds == 0b01111111) || (self->superState == SUPERSTATE_SUPER && self->up && controller->keyY.press))) {
		ext->blend.state = HYPERBLEND_FADEIN;
		ext->blend.amount = 0;
		ext->is_hyper = true;
		ext->can_dash = true; // this was added solely to replicate the dashing out of transform thing from S3&K

		if (self->up && controller->keyY.press) {
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

	if (!ERZStart && HM_globals->config.twoHeavensMode && Zone->timer & 1) {
		--self->superRingLossTimer;
	}

	// ERZ shit ------------------------------------------------------------
#if MANIA_USE_PLUS
	if (Player->superDashCooldown == 30) {
#else
	if (ERZStart->superDashCooldown == 30) {
#endif
		HMAPI_BadnikScreenClear(self);
		RSDK.SetChannelAttributes(RSDK.PlaySfx(Player->sfxRelease, false, 0xFF), 1.1, 0.0, 1.0);
		const int32 vel = TO_FIXED(2);
		for (int32 i = 0; i != 4; ++i) {
			EntityDebris* debris = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
			debris->timer = 17;
			debris->velocity.x = vel - vel * (2 * (i & 1));
			debris->velocity.y = vel - vel * (i & 2);
			debris->drawGroup = self->drawGroup;
			RSDK.SetSpriteAnimation(HyperStars->aniFrames, 0, &debris->animator, true, 3);
			if (self->drawFX & FX_SCALE) {
				debris->drawFX |= FX_SCALE;
				debris->scale.x = self->scale.x;
				debris->scale.y = self->scale.y;
			}
		}
	}

	// encore shit ---------------------------------------------------------
#if MANIA_USE_PLUS
	if (ext->prev_ID != self->characterID) {
		PlayerExt* sidekick_ext = (PlayerExt*)GetExtMem(SLOT_PLAYER2);
		if (sidekick_ext && ext->prev_ID == RSDK_GET_ENTITY(SLOT_PLAYER2, Player)->characterID) {
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

		if (HM_globals->config.hyperStyle != 1 || info->rows != 1) {
			if (ext->blend.amount >= 0x100) {
				if (self->superState == SUPERSTATE_SUPER || self->superBlendState != 1) {
					ext->blend.amount = 0;
					if (HM_globals->config.hyperStyle != 2) {
						ext->blend.state = (ext->blend.state + 1) % (info->rows * 2);
					} else {
						ext->blend.state = (ext->blend.state + 1) % (6 * 2);
					}
				}
			} else {
				ext->blend.amount += (ext->blend.state < 0) ? 8
				                                            : 16 + 24 * (ext->blend.state & 1);
			}

			color colorStore[12];
			for (int32 i = 0; i != 6; ++i) {
				colorStore[i] = RSDK.GetPaletteEntry(6, info->startIndex + i);
				colorStore[i + 6] = RSDK.GetPaletteEntry(7, info->startIndex + i);
			}

			// paletteSlot and bankID are usually the same value but theyre seperate arguments just in case
			Player_BlendHyperPalette(0, 0, info);
			if (FarPlane) {
				RSDK.CopyPalette(0, info->startIndex, 3, info->startIndex, 6);
			} else if (OOZSetup) {
				RSDK.CopyPalette(0, info->startIndex, 1, info->startIndex, 6);
				RSDK.CopyPalette(0, info->startIndex, 2, info->startIndex, 6);
			} else if (HCZSetup) {
				Player_BlendHyperPalette(1, 1, info);
			} else if (CPZSetup) {
				Player_BlendHyperPalette(2, 2, info);
			}

			for (int32 i = 0; i != 6; ++i) {
				RSDK.SetPaletteEntry(6, info->startIndex + i, colorStore[i]);
				RSDK.SetPaletteEntry(7, info->startIndex + i, colorStore[i + 6]);
			}
		}
	}

	// extra abilities -----------------------------------------------------
	if (self->superState == SUPERSTATE_SUPER) {
		self->drownTimer = 0;

		if (self->characterID == ID_SONIC && ext->can_dash && self->jumpPress && self->state == Player_State_Air) {
			Player_HyperSonicDash();
			ext->can_dash = false;
		}

		Entity* entity = RSDK_GET_ENTITY_GEN(self->playerID + Player->playerCount);
		if (entity->classID != HyperStars->classID) {
			if (index != -1 && HM_globals->config.hyperStyle == 1 && PlayerPaletteDefs[index].rows == 1) {
				destroyEntity(entity);
			} else {
				RSDK.ResetEntity(entity, HyperStars->classID, self);
			}
		}
		if (self->characterID == ID_TAILS) {
			entity = RSDK_GET_ENTITY_GEN(SuperFlickySlot);
			if (entity->classID != SuperFlicky->classID) RSDK.ResetEntity(entity, SuperFlicky->classID, self);
		}
		if (((void*)self->state == (void*)Player_State_KnuxGlideLeft && self->left)
		|| ((void*)self->state == (void*)Player_State_KnuxGlideRight && self->right)) {
			// gliding momentum retention
			if (HM_globals->config.GSWburst && ext->prev_state != (void*)Player_State_KnuxGlideLeft && ext->prev_state != (void*)Player_State_KnuxGlideRight) {
				EntityCamera* camera = self->camera;
				if (camera && !Zone->autoScrollSpeed) {
					self->scrollDelay = 8;
					camera->state     = Camera_State_FollowY;
				}

				EntityDebris* shockwave = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
				shockwave->timer      = 11;
				shockwave->inkEffect  = INK_ADD;
				shockwave->alpha      = 0x100;
				shockwave->drawGroup  = self->drawGroup + 1;
				shockwave->drawFX    |= FX_FLIP;
				shockwave->direction  = self->direction;
				RSDK.SetSpriteAnimation(PlayerStaticExt.shockwaveFrames, 0, &shockwave->animator, true, 0);
				// its doing that thing where it corrupts when it scales and i have no idea what's causing it and it makes me want to scream at the top of my fucking lungs until my voice box bursts
				/*if (self->drawFX & FX_SCALE) {
					shockwave->drawFX |= FX_SCALE;
					shockwave->scale.x = self->scale.x >> 1;
					shockwave->scale.y = self->scale.y >> 1;
				}*/

				RSDK.SetChannelAttributes(RSDK.PlaySfx(Player->sfxRelease, false, 0xFF), 1.1, 0.0, 0.65);
				RSDK.SetChannelAttributes(RSDK.PlaySfx(PlayerStaticExt.sfxEarthquake2, false, 0xFF), 1.0, 0.0, 1.6);

				self->velocity.x = 0x80000 * (self->direction ? -1 : 1);
				if (self->velocity.x > 0 && ext->prev_xvel > self->velocity.x) self->velocity.x = ext->prev_xvel;
				if (self->velocity.x < 0 && ext->prev_xvel < self->velocity.x) self->velocity.x = ext->prev_xvel;
				self->abilitySpeed = self->velocity.x / RSDK.Cos512(self->timer) << 9;
			}

			// earthquake
			if (abs(ext->prev_xvel) >= 0x48000 && self->velocity.x == 0 && self->abilitySpeed != 0) {
				Camera_ShakeScreen(RSDK.GetEntitySlot(self), 6, 0);
				RSDK.StopSfx(Player->sfxGrab);
				RSDK.PlaySfx(PlayerStaticExt.sfxEarthquake, false, 0xFF);
				RSDK.SetChannelAttributes(RSDK.PlaySfx(PlayerStaticExt.sfxEarthquake2, false, 0xFF), 0.6, 0.0, 1.0);
				HMAPI_BadnikScreenClear(self);
				HMAPI_ItemBoxScreenClear(self, false);
			}
		}
	}

	// music handling ------------------------------------------------------
	if (!ERZStart && HM_globals->config.enableHyperMusic && Music->trackLoops[TRACK_SUPER] != HM_globals->config.hyperMusicLoopPoint &&
	(Music->activeTrack == TRACK_SUPER || !HM_globals->config.twoHeavensMode)) {
#if MANIA_USE_PLUS
		Music_SetMusicTrack("Hyper.ogg", TRACK_SUPER, HM_globals->config.hyperMusicLoopPoint);
		if (Music->activeTrack == TRACK_SUPER) Music_PlayJingle(TRACK_SUPER);
#else
		//Music_TransitionTrack(TRACK_HYPER, 1.0);
#endif
	}
}

bool32 Player_State_Ground_HOOK(bool32 skippedState) {
	RSDK_THIS(Player);
	if (!Player_IsHyper(self)) return false;
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));
#if MANIA_USE_PLUS
	if (self->characterID == ID_MIGHTY) ext->can_dash = true;
	ext->glide_timer = 0;
#endif
	if (self->characterID == ID_SONIC) ext->can_dash = false;
	return false;
}

bool32 Player_JumpAbility_Sonic_HOOK(bool32 skippedState) {
	RSDK_THIS(Player);
	if (!Player_IsHyper(self)) return false;
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));

	if (self->jumpAbilityState == 1 && self->jumpPress) Player_HyperSonicDash();
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
	&& self->jumpPress && self->jumpAbilityState == 0 && self->animator.animationID == ANI_HAMMERDROP
#if MANIA_USE_PLUS
	&& (self->stateInput != Player_Input_P2_AI || (self->up && globals->gameMode != MODE_ENCORE))) {
#else
	&& self->stateInput != Player_Input_P2_AI) {
#endif
		self->velocity.y *= 2;
		RSDK.StopSfx(Player->sfxRelease);
		RSDK.PlaySfx(Player->sfxPeelRelease, false, 0xFF);
	}
	return false;
}

bool32 Player_State_MightyHammerDrop_HOOK(bool32 skippedState) {
	if (skippedState) return true;
	RSDK_THIS(Player);

	if (self->onGround) {
		self->controlLock = 0;
		self->onGround    = false;

		PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));
		int32 dropForce = self->gravityStrength + (self->underwater == 1 ? 0x10000 : 0x20000);
		if (Player_IsHyper(self)) {
			if (!HM_globals->config.JEAjank) dropForce *= 3;
			if (ext->can_dash) {
				HMAPI_ScreenFlash(self, 0.75);
				HMAPI_BadnikScreenClear(self);
				RSDK.PlaySfx(PlayerStaticExt.sfxEarthquake, false, 0xFF);
			}
		}
		int32 groundVel = self->groundVel - (self->groundVel >> 2);

		self->velocity.x = (groundVel * RSDK.Cos256(self->angle) + dropForce * RSDK.Sin256(self->angle)) >> 8;
		self->velocity.y = (groundVel * RSDK.Sin256(self->angle) - dropForce * RSDK.Cos256(self->angle)) >> 8;
		if (HM_globals->config.JEAjank && Player_IsHyper(self)) {
			if (ext->can_dash) {
				self->velocity.x *= 3;
				self->velocity.y *= 3;
			} else {
				self->velocity.x *= 2;
				self->velocity.y *= 2;
			}
		}

		Player_Gravity_True();

		RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);

		self->animator.speed = MIN((abs(self->groundVel) >> 12) + 0x30, 0xF0);

		RSDK.StopSfx(Player->sfxMightyDrill);
		RSDK.PlaySfx(Player->sfxMightyLand, false, 0xFF);
		if (Player_IsHyper(self) && ext->can_dash) {
			Camera_ShakeScreen(RSDK.GetEntitySlot(self), 4, 12);
		} else {
			Camera_ShakeScreen(RSDK.GetEntitySlot(self), 0, 4);
		}
		ext->can_dash = false;

		Hitbox *hitbox = RSDK.GetHitbox(&self->animator, 0);
		Player_SpawnMightyHammerdropDust(0x10000, hitbox);
		Player_SpawnMightyHammerdropDust(-0x10000, hitbox);
		Player_SpawnMightyHammerdropDust(0x18000, hitbox);
		Player_SpawnMightyHammerdropDust(-0x18000, hitbox);
		Player_SpawnMightyHammerdropDust(0x20000, hitbox);
		Player_SpawnMightyHammerdropDust(-0x20000, hitbox);

		self->angle            = 0;
		self->collisionMode    = CMODE_FLOOR;
		self->applyJumpCap     = false;
		self->jumpAbilityState = (Player_IsHyper(self)) ? 1 : 3;

		if (self->invincibleTimer > 0) {
			if (self->invincibleTimer < 8)
				self->invincibleTimer = 8;
			self->state = Player_State_Air;
		}
		else {
			self->invincibleTimer = -8;
			self->state           = Player_State_Air;
		}
	}
	else {
		Player_HandleAirFriction();
		Player_HandleAirMovement();

		if (self->velocity.y <= 0x10000) {
			self->state = Player_State_Air;
			RSDK.SetSpriteAnimation(self->aniFrames, ANI_JUMP, &self->animator, false, 0);
		}
	}
	return true;
}

bool32 Player_State_RayGlide_HOOK(bool32 skippedState) {
	RSDK_THIS(Player);
	if (!Player_IsHyper(self)) return false;
	PlayerExt* ext = (PlayerExt*)GetExtMem(RSDK.GetEntitySlot(self));

	if (ext->can_dash && self->rotation) {
		ext->can_dash = false;
		if (self->abilitySpeed > -0x20000) self->abilitySpeed = -0x20000;

		EntityJetGlideEffect* effect = CREATE_ENTITY(JetGlideEffect, NULL, self->position.x, self->position.y);
		effect->drawGroup = self->drawGroup + 1;

		Hitbox hitbox;
		hitbox.left   = -100;
		hitbox.top    = -100;
		hitbox.right  = 100;
		hitbox.bottom = 100;

		foreach_all(Ring, ring) {
			if (ring->state != Ring_State_Sparkle
			 && RSDK.CheckObjectCollisionTouchBox(self, &hitbox, ring, &Ring->hitbox)) {
				ring->state = Ring_UnconditionalAttract;
				ring->storedPlayer = self;
			}
		}

		for (int16 i = 0; i != ENTITY_COUNT; ++i) {
			Entity* entity = RSDK_GET_ENTITY_GEN(i);
			const attackinfo_t* info = IsATKEntity(entity, ATKFLAG_ISBOSS, false);
			if (!info) continue;

			const Vector2 old_pos = entity->position;
			if (info->adjustPos) info->adjustPos(entity);
			if (RSDK.CheckObjectCollisionTouchBox(self, &hitbox, entity, info->getHitbox(entity))) info->onHit(self, entity);
			entity->position = old_pos;
		}
		ext->glide_timer = 0;

		RSDK.SetChannelAttributes(RSDK.PlaySfx(PlayerStaticExt.sfxJetGlide, false, 0xFF), 1.5, 0.0, 1.0);
		RSDK.SetChannelAttributes(RSDK.PlaySfx(Player->sfxRelease, false, 0xFF), 1.1, 0.0, 1.0);
		RSDK.SetChannelAttributes(RSDK.PlaySfx(ItemBox->sfxHyperRing, false, 0xFF), 0.4, 0.0, 1.0);
	}
	if (!self->rotation) {
		ext->can_dash = true;
	}

	if (((self->direction == FLIP_X && self->right) || (self->direction == FLIP_NONE && self->left))
	 && self->rotation && ext->glide_timer < 60) {
		if (!self->abilitySpeed) {
			self->velocity.y -= (self->gravityStrength * RSDK.Cos512(self->abilityValue)) >> 9;
		}
	 	if (self->direction) {
			self->velocity.x += (22 * RSDK.Sin256(0x50 - self->abilityValue)) >> (uint8)(self->underwater != false);
		} else  {
			self->velocity.x -= (22 * RSDK.Sin256(0x50 - self->abilityValue)) >> (uint8)(self->underwater != false);
		}

		if (!(Zone->timer % 2)) {
			int32 sin = RSDK.Sin256(Zone->timer * 3) * 0xFF;
			EntityDebris* sparkle = CREATE_ENTITY(Debris, Debris_State_Move, sin * 20 + self->position.x, self->position.y);
			sparkle->timer        = 12;
			sparkle->inkEffect    = INK_ADD;
			sparkle->alpha        = 0x100;
			sparkle->drawGroup    = self->drawGroup;
			RSDK.SetSpriteAnimation(HyperStars->aniFrames, 1, &sparkle->animator, true, 0);
			sparkle = CREATE_ENTITY(Debris, Debris_State_Move, -sin * 20 + self->position.x, self->position.y);
			sparkle->timer        = 12;
			sparkle->inkEffect    = INK_ADD;
			sparkle->alpha        = 0x100;
			sparkle->drawGroup    = self->drawGroup;
			RSDK.SetSpriteAnimation(HyperStars->aniFrames, 1, &sparkle->animator, true, 0);
		}
		++ext->glide_timer;
	}

	if ((self->direction == FLIP_X && !self->right) || (self->direction == FLIP_NONE && !self->left)) {
		ext->glide_timer = 60;
	}

	return false;
}

void Ring_UnconditionalAttract() {
	RSDK_THIS(Ring);

	EntityPlayer* player = self->storedPlayer;
	int32 startX = self->position.x;
	int32 startY = self->position.y;

	if (self->position.x <= player->position.x) {
		if (self->velocity.x >= 0)
			self->velocity.x += 0x3000;
		else
			self->velocity.x += 0xC000;
	} else {
		if (self->velocity.x <= 0)
			self->velocity.x -= 0x3000;
		else
			self->velocity.x -= 0xC000;
	}

	if (startY <= player->position.y) {
		if (self->velocity.y >= 0)
			self->velocity.y += 0x3000;
		else
			self->velocity.y += 0xC000;
	} else {
		if (self->velocity.y <= 0)
			self->velocity.y -= 0x3000;
		else
			self->velocity.y -= 0xC000;
	}

	self->position.x = startX + self->velocity.x;
	self->position.y = startY + self->velocity.y;
	Ring_Collect();

	self->animator.frameID = Zone->ringFrame;
}

void Player_HyperSonicDash() {
	RSDK_THIS(Player);

	if (!(self->up || self->down || self->left || self->right)) {
		if (!HM_globals->config.hyperFlashForwarding) return;
		self->velocity.x = 0x80000 * (self->direction ? -1 : 1);
		self->velocity.y = 0;
	} else {
		self->velocity.x = 0x80000 * (self->right - self->left);
		self->velocity.y = 0x80000 * (self->down - self->up);
	}
	if (globals->medalMods & MEDAL_NODROPDASH) {
		self->jumpAbilityState = 0;
	} else {
		if (HM_globals->config.hyperFlashDropDash) self->jumpAbilityState = 22;
	}
	HMAPI_ScreenFlash(self, 1.0);
	HMAPI_BadnikScreenClear(self);

	RSDK.SetChannelAttributes(RSDK.PlaySfx(Player->sfxRelease, false, 0xFF), 1.1, 0.0, 1.0);
	RSDK.SetChannelAttributes(RSDK.PlaySfx(ItemBox->sfxHyperRing, false, 0xFF), 0.4, 0.0, 1.0);
	EntityCamera* camera = self->camera;
	if (camera && !Zone->autoScrollSpeed) {
		self->scrollDelay = 15;
		camera->state     = Camera_State_FollowY;
	}

	const int32 vel = TO_FIXED(2);
	for (int32 i = 0; i != 4; ++i) {
		EntityDebris* debris = CREATE_ENTITY(Debris, Debris_State_Move, self->position.x, self->position.y);
		debris->timer = 17;
		debris->velocity.x = vel - vel * (2 * (i & 1));
		debris->velocity.y = vel - vel * (i & 2);
		debris->drawGroup = self->drawGroup;
		RSDK.SetSpriteAnimation(HyperStars->aniFrames, 0, &debris->animator, true, 3);
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
	color* palette = info->colors[paletteSlot];
	if (HM_globals->config.hyperStyle == 2 && info->rows == 1) palette = PlayerPaletteDefs[0].colors[paletteSlot];

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
