#include "SuperFlicky.h"
#include "Debris.h"
#include "Player.h"
#include "Zone.h"

#include "CPZ/CPZSetup.h"
#include "OOZ/OOZSetup.h"
#include "HCZ/HCZSetup.h"
#include "MMZ/FarPlane.h"

ObjectSuperFlicky* SuperFlicky;

void SuperFlicky_Update(void) {
	RSDK_THIS(SuperFlicky);

	if (self->player && (self->player->characterID != ID_TAILS || !Player_IsHyper(self->player))
	 && self->blend.state != 1) {
		RSDK.PlaySfx(SuperFlicky->sfxFlee, false, 0xFF);
	}

	bool32 all_offscreen = true;
	for (int32 i = 0; i != SUPERFLICKY_COUNT; ++i) {
		self->instanceOsc[i] += 2;
		Vector2 target_pos = { 0, 0 };
		SuperFlicky_HandleAttack(i);
		if (self->player) {
			if (self->player->characterID != ID_TAILS || !Player_IsHyper(self->player)) {
				target_pos = (Vector2){
					self->player->position.x - 0xC00000 + 0xC00000 * (2 * (i & 1)),
					self->player->position.y - 0xC00000 + 0xC00000 * (i & 2)
				};
			} else if (self->instanceTarget[i]) {
				const attackinfo_t* info = GetATKClassInfo(self->instanceTarget[i]->classID);
				const Vector2 old_pos = self->instanceTarget[i]->position;
				const Hitbox* hitbox = info->getHitbox(self->instanceTarget[i]);
				if (info->adjustPos) info->adjustPos(self->instanceTarget[i]);
				target_pos = (Vector2){
					self->instanceTarget[i]->position.x + (hitbox->right + hitbox->left) * 0xFFFF / 2,
					self->instanceTarget[i]->position.y + (hitbox->bottom + hitbox->top) * 0xFFFF / 2
				};
				self->instanceTarget[i]->position = old_pos;
			} else {
				target_pos = (Vector2){
					self->player->position.x + (RSDK.Sin256(self->instanceOsc[i]) * 2 << 12),
					self->player->position.y - 0x200000 + (RSDK.Cos256(self->instanceOsc[i]) * 2 << 11)
				};
			}
		}

		int32 acceleration = 0;
		if (target_pos.x < self->instancePos[i].x) {
			acceleration = -0x2000;
			if (self->instanceVel[i].x >= 0) acceleration *= 4;
		} else {
			acceleration = 0x2000;
			if (self->instanceVel[i].x < 0) acceleration *= 4;
		}
		self->instanceVel[i].x += acceleration;

		// TODO we could probably simplify this with CLAMP
		bool32 flyUp = (target_pos.y - self->instancePos[i].y < 0);
		if (self->instanceVel[i].y <= -0x100000) {
			flyUp = false;
		} else if (self->instanceVel[i].y >= 0x100000) {
			flyUp = true;
		}
		if (flyUp) {
			acceleration = -0x2000;
			if (self->instanceVel[i].y >= 0) acceleration *= 4;
		} else {
			acceleration = 0x2000;
			if (self->instanceVel[i].y < 0) acceleration *= 4;
		}
		self->instanceVel[i].y += acceleration;

		self->instancePos[i].x += self->instanceVel[i].x;
		self->instancePos[i].y += self->instanceVel[i].y;
		self->position.x = self->instancePos[i].x;
		self->position.y = self->instancePos[i].y;

		if (self->instanceTarget[i]) {
			if (self->instanceTarget[i]->classID == TYPE_BLANK) {
				self->instanceTarget[i] = NULL;
			} else {
				const attackinfo_t* info = GetATKClassInfo(self->instanceTarget[i]->classID);
				const Vector2 old_pos = self->instanceTarget[i]->position;
				const uint32 index = self->instanceTarget[i]->classID - HM_globals->AttackableClasses_startidx;
				if (info->adjustPos) info->adjustPos(self->instanceTarget[i]);

				if (RSDK.CheckObjectCollisionTouchBox(self, &SuperFlicky->hitbox, self->instanceTarget[i], info->getHitbox(self->instanceTarget[i]))) {
					info->onHit(self->player, self->instanceTarget[i]);
					self->instanceTarget[i]->position = old_pos;
					self->instanceTarget[i] = NULL;
					self->instanceCooldown[i] = 120;
				}
				if (self->instanceTarget[i]) self->instanceTarget[i]->position = old_pos;
			}
		}

		if (self->player->characterID == ID_TAILS && Player_IsHyper(self->player) && !(Zone->timer & 7)) {
			EntityDebris* sparkle = CREATE_ENTITY(Debris, NULL, self->instancePos[i].x + RSDK.Rand(-TO_FIXED(8), TO_FIXED(8)), self->instancePos[i].y + RSDK.Rand(-TO_FIXED(8), TO_FIXED(8)));
			sparkle->velocity.y = -0x8000;
			sparkle->state      = Debris_State_Move;
			sparkle->timer      = 14 - (Zone->timer & 1);
			sparkle->inkEffect  = INK_ADD;
			sparkle->alpha      = 0x100;
			sparkle->drawGroup  = self->drawGroup + 1;
			RSDK.SetSpriteAnimation(HyperStars->aniFrames, 1, &sparkle->animator, true, Zone->timer & 1);
		}
		RSDK.ProcessAnimation(&self->instanceAnimator[i]);

		Vector2 range = { 4, 4 };
		if (all_offscreen) all_offscreen = (!RSDK.CheckOnScreen(self, &range));
	}

	if ((self->player->characterID != ID_TAILS || !Player_IsHyper(self->player)) && all_offscreen) {
		destroyEntity(self);
	}

	self->drawGroup = self->player->drawGroup;

	// handling blend variables
	bool32 is_hyper = self->player->characterID == ID_TAILS && Player_IsHyper(self->player);
	if (is_hyper && self->blend.state == 1) {
		self->blend.state = 0;
		self->blend.amount = 0;
	}
	if (!is_hyper && self->blend.state != 1) {
		self->blend.state = 1;
		self->blend.amount = 0x100;
	}
	if (is_hyper || self->blend.state) {
		if (self->blend.state & 1) {
			if (self->blend.amount <= 0) {
				if (is_hyper) self->blend.state &= 2;
			} else {
				self->blend.amount -= 16;
			}
		} else {
			self->blend.amount += 16;
			if (self->blend.amount >= 256) self->blend.state |= 1;
			if (self->blend.state == 1) self->blend.state = 2;
		}
	}
}

void SuperFlicky_LateUpdate(void) {
}

void SuperFlicky_StaticUpdate(void) {
}

void SuperFlicky_Draw(void) {
	RSDK_THIS(SuperFlicky);
	bool32 is_hyper = self->player->characterID == ID_TAILS && Player_IsHyper(self->player);

	if (self->player->isChibi) {
		self->scale.x = 0x100;
		self->scale.y = 0x100;
	} else {
		if (self->player->drawFX & FX_SCALE)
			self->drawFX |= FX_SCALE;
		else
			self->drawFX &= ~FX_SCALE;
		self->scale.x = self->player->scale.x;
		self->scale.y = self->player->scale.y;
	}

	color colorStore[SUPERFLICKY_COLOR_COUNT * 3];
	if (self->blend.state || self->blend.amount) {
		// storing unmodified palettes for later
		for (int32 i = 0; i != SUPERFLICKY_COLOR_COUNT; ++i) {
			if (HCZSetup) colorStore[SUPERFLICKY_COLOR_COUNT + i] = RSDK.GetPaletteEntry(1, 2 + i);
			if (CPZSetup) colorStore[SUPERFLICKY_COLOR_COUNT * 2 + i] = RSDK.GetPaletteEntry(2, 2 + i);
			colorStore[i] = RSDK.GetPaletteEntry(0, 2 + i);
		}

		// fading palettes
		//   underwater palettes
		if (HCZSetup) {
			for (int32 i = 0; i != SUPERFLICKY_COLOR_COUNT; ++i) {
				const int32 superIndex = MIN(i * 2, 5);
				RSDK.SetPaletteEntry(6, 2 + i, Player->superPalette_Sonic_HCZ[6 + superIndex]);
				if (self->blend.state & 2) RSDK.SetPaletteEntry(7, 2 + i, Player->superPalette_Sonic_HCZ[12 + superIndex]);
			}
			SuperFlicky_BlendSuperPalette(1);
		} else if (CPZSetup) {
			for (int32 i = 0; i != SUPERFLICKY_COLOR_COUNT; ++i) {
				const int32 superIndex = MIN(i * 2, 5);
				RSDK.SetPaletteEntry(6, 2 + i, Player->superPalette_Sonic_CPZ[6 + superIndex]);
				if (self->blend.state & 2) RSDK.SetPaletteEntry(7, 2 + i, Player->superPalette_Sonic_CPZ[12 + superIndex]);
			}
			SuperFlicky_BlendSuperPalette(2);
		}

		//   normal palette
		for (int32 i = 0; i != SUPERFLICKY_COLOR_COUNT; ++i) {
			const int32 superIndex = MIN(i * 2, 5);
			RSDK.SetPaletteEntry(6, 2 + i, Player->superPalette_Sonic[6 + superIndex]);
			if (self->blend.state & 2) RSDK.SetPaletteEntry(7, 2 + i, Player->superPalette_Sonic[12 + superIndex]);
		}
		SuperFlicky_BlendSuperPalette(0);
	}

	// drawing
	for (int32 i = 0; i != SUPERFLICKY_COUNT; ++i) {
		self->direction = (self->instanceVel[i].x < 0);
		RSDK.DrawSprite(&self->instanceAnimator[i], &self->instancePos[i], false);
	}

	// reverting original palettes
	if (self->blend.state || self->blend.amount) {
		for (int32 i = 0; i != SUPERFLICKY_COLOR_COUNT; ++i) {
			if (HCZSetup) RSDK.SetPaletteEntry(1, 2 + i, colorStore[SUPERFLICKY_COLOR_COUNT + i]);
			if (CPZSetup) RSDK.SetPaletteEntry(2, 2 + i, colorStore[SUPERFLICKY_COLOR_COUNT * 2 + i]);
			RSDK.SetPaletteEntry(0, 2 + i, colorStore[i]);
		}
	}
	
}

void SuperFlicky_Create(void* data) {
	RSDK_THIS(SuperFlicky);
	self->visible   = true;
	self->drawFX    = FX_FLIP;
	self->active    = ACTIVE_NORMAL;

	if (data && ((Entity*)data)->classID == Player->classID) {
		self->player = (EntityPlayer*)data;
		self->position.x = self->player->position.x;
		self->position.y = self->player->position.y;
	}

	const int32 osc_add = 0x100 / SUPERFLICKY_COUNT;
	for (int32 i = 0; i != SUPERFLICKY_COUNT; ++i) {
		self->instanceOsc[i] = i * osc_add;
		self->instancePos[i].x = self->position.x - 0xC00000 + 0xC00000 * (2 * (i & 1));
		self->instancePos[i].y = self->position.y - 0xC00000 + 0xC00000 * (i & 2);
		RSDK.SetSpriteAnimation(SuperFlicky->aniFrames, 1, &self->instanceAnimator[i], true, 0);
	}
}

void SuperFlicky_StageLoad(void) {
	SuperFlicky->aniFrames = RSDK.LoadSpriteAnimation("Global/SuperFlicky.bin", SCOPE_STAGE);

	SuperFlicky->hitbox.left   = -4;
	SuperFlicky->hitbox.top    = -4;
	SuperFlicky->hitbox.right  = 4;
	SuperFlicky->hitbox.bottom = 4;
	SuperFlicky->sfxFlee = RSDK.GetSfx("Global/FlickyFlee.wav");
}

#if RETRO_INCLUDE_EDITOR
void SuperFlicky_EditorDraw(void) { SuperFlicky_Draw(); }
void SuperFlicky_EditorLoad(void) {}
#endif
void SuperFlicky_Serialize(void) {}

void SuperFlicky_HandleAttack(int32 slot) {
	RSDK_THIS(SuperFlicky);

	if (!self->instanceTarget[slot]) {
		if (self->instanceCooldown[slot]) {
			--self->instanceCooldown[slot];
		} else {
			SuperFlicky_TryFindValidTarget(slot);
		}
		return;
	}

	const attackinfo_t* info = IsATKEntity(self->instanceTarget[slot], ATKFLAG_NONE, false);
	if (self->instanceTarget[slot]->active == ACTIVE_DISABLED || !info || !info->checkVulnerable(self->instanceTarget[slot])) {
		self->instanceTarget[slot] = NULL;
		self->instanceCooldown[slot] = 120; // TODO is this even supposed to happen? make sure to check AIR code later
	}
}

void SuperFlicky_TryFindValidTarget(int32 slot) {
	RSDK_THIS(SuperFlicky);

	for (int16 i = 0; i != ENTITY_COUNT; ++i) {
		Entity* entity = RSDK_GET_ENTITY_GEN(i);
		if (!IsATKEntity(entity, ATKFLAG_NONE, true)) continue;
		if (FarPlane && ((self->drawGroup >= 3 && entity->drawGroup < 3) || (self->drawGroup < 3 && entity->drawGroup >= 3))) continue;

		// checking if its already being targeted by another flicky
		bool32 is_victim = false;
		for (int32 l = 0; l != SUPERFLICKY_COUNT; ++l) {
			if (l == slot) continue;
			if (self->instanceTarget[l] == entity) {
				is_victim = true;
				break;
			}
		}
		if (is_victim) continue;

		self->instanceTarget[slot] = entity;
		break;
	}
}

void SuperFlicky_BlendSuperPalette(int32 bankID) {
	RSDK_THIS(SuperFlicky);
	if (self->blend.state & 2) {
		RSDK.SetLimitedFade(bankID, 6, 7, self->blend.amount, 2, 2 + SUPERFLICKY_COUNT - 1);
	} else {
		RSDK.SetLimitedFade(bankID, bankID, 6, self->blend.amount, 2, 2 + SUPERFLICKY_COUNT - 1);
	}
}
