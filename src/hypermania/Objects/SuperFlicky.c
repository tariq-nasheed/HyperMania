#include "SuperFlicky.h"
#include "Debris.h"
#include "Player.h"
#include "Zone.h"

// NOTE FOR THE FUTURE WHEN ADDING BOSS SUPPORT: cooldown resets after hitting boss while not changing target (this will mean adding some sort of per-instance IsAttacking bool)
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
				if (!IsAttackableEntity(self->instanceTarget[i], 0)) {
					target_pos = (Vector2){
						self->instanceTarget[i]->position.x,
						self->instanceTarget[i]->position.y
					};
				} else {
					const Vector2 old_pos = self->instanceTarget[i]->position;
					const uint32 index = self->instanceTarget[i]->classID - AttackableClasses_startidx;
					if (AttackableClasses[index].adjustPos) AttackableClasses[index].adjustPos(self->instanceTarget[i]);
					target_pos = (Vector2){
						self->instanceTarget[i]->position.x,
						self->instanceTarget[i]->position.y
					};
					self->instanceTarget[i]->position = old_pos;
				}
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
			if (!IsAttackableEntity(self->instanceTarget[i], 0)) {
				Hitbox* hitbox = GetEnemyHitbox(self->instanceTarget[i]);
				if (RSDK.CheckObjectCollisionTouchBox(self, &SuperFlicky->hitbox, self->instanceTarget[i], hitbox)) {
					HitEnemy(self->player, self->instanceTarget[i]);
					self->instanceTarget[i] = NULL;
					self->instanceCooldown[i] = 120;
				}
			} else {
				const Vector2 old_pos = self->instanceTarget[i]->position;
				const uint32 index = self->instanceTarget[i]->classID - AttackableClasses_startidx;
				if (AttackableClasses[index].adjustPos) AttackableClasses[index].adjustPos(self->instanceTarget[i]);

				if (RSDK.CheckObjectCollisionTouchBox(self, &SuperFlicky->hitbox, self->instanceTarget[i], AttackableClasses[index].getHitbox(self->instanceTarget[i]))) {
					AttackableClasses[index].onHit(self->player, self->instanceTarget[i]);
					self->instanceTarget[i] = NULL;
					self->instanceCooldown[i] = 120;
				}
				if (self->instanceTarget[i]) self->instanceTarget[i]->position = old_pos;
			}
		}

		if (self->player->characterID == ID_TAILS && Player_IsHyper(self->player) && !(Zone->timer & 7)) {
			EntityDebris* sparkle = CREATE_ENTITY(Debris, NULL, self->instancePos[i].x, self->instancePos[i].y);
			sparkle->state        = Debris_State_Move;
			sparkle->timer        = 12;
			sparkle->inkEffect    = INK_ADD;
			sparkle->alpha        = 0x100;
			sparkle->drawGroup    = Zone->objectDrawGroup[1];
			RSDK.SetSpriteAnimation(HyperStars->aniFrames, 1, &sparkle->animator, true, 0 + 0);
		}
		RSDK.ProcessAnimation(&self->instanceAnimator[i]);

		Vector2 range = { 4, 4 };
		if (all_offscreen) all_offscreen = (!RSDK.CheckOnScreen(self, &range));
	}

	if ((self->player->characterID != ID_TAILS || !Player_IsHyper(self->player)) && all_offscreen) {
		destroyEntity(self);
	}
}

void SuperFlicky_LateUpdate(void) {
}

void SuperFlicky_StaticUpdate(void) {
}

void SuperFlicky_Draw(void) {
	RSDK_THIS(SuperFlicky);
	bool32 is_hyper = self->player->characterID == ID_TAILS && Player_IsHyper(self->player);

	// handling blend variables
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

	// loading up palettes into banks
	color colorStore[3];
	if (self->blend.state || self->blend.amount) {
		for (int32 i = 0; i != 3; ++i) {
			colorStore[i] = RSDK.GetPaletteEntry(0, i + 2);
			RSDK.SetPaletteEntry(6, i + 2, Player->superPalette_Sonic[i * 2 + 6]);
			if (self->blend.state & 2) RSDK.SetPaletteEntry(7, i + 2, Player->superPalette_Sonic[i * 2 + 12]);
		}
	}

	// fading palettes
	if (self->blend.state || self->blend.amount) {
		if (self->blend.state & 2) {
			RSDK.SetLimitedFade(0, 6, 7, self->blend.amount, 2, 4);
		} else {
			RSDK.SetLimitedFade(0, 0, 6, self->blend.amount, 2, 4);
		}
	}

	// drawing
	for (int32 i = 0; i != SUPERFLICKY_COUNT; ++i) {
		self->direction = (self->instanceVel[i].x < 0);
		RSDK.DrawSprite(&self->instanceAnimator[i], &self->instancePos[i], false);
	}

	// reverting to original palette
	if (self->blend.state || self->blend.amount) {
		for (int32 i = 0; i != 3; ++i) {
			RSDK.SetPaletteEntry(0, i + 2, colorStore[i]);
		}
	}
}

void SuperFlicky_Create(void* data) {
	RSDK_THIS(SuperFlicky);
	self->visible   = true;
	self->drawFX    = FX_FLIP;
	self->drawGroup = Zone->objectDrawGroup[1];
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

	if ((!IsAttackableEntity(self->instanceTarget[slot], 0) && !IsVulnerableEnemy(self->instanceTarget[slot], true))
	 || self->instanceTarget[slot]->active == ACTIVE_DISABLED) {
		const Vector2 old_pos = self->instanceTarget[slot]->position;
		if (IsAttackableEntity(self->instanceTarget[slot], 0)) {
			const uint32 index = self->instanceTarget[slot]->classID - AttackableClasses_startidx;
			if (AttackableClasses[index].adjustPos) AttackableClasses[index].adjustPos(self->instanceTarget[slot]);
		}
		const bool32 visible = RSDK.CheckOnScreen(self->instanceTarget[slot], NULL);
		self->instanceTarget[slot]->position = old_pos;

		if (!visible) {
			self->instanceTarget[slot] = NULL;
			self->instanceCooldown[slot] = 0x78;
		}
	}
}

void SuperFlicky_TryFindValidTarget(int32 slot) {
	RSDK_THIS(SuperFlicky);

	for (int16 i = 0; i != ENTITY_COUNT; ++i) {
		Entity* entity = RSDK_GET_ENTITY_GEN(i);

		// checking if potential victim is already being targeted by another flicky
		bool32 is_victim = false;
		for (int32 l = 0; l != SUPERFLICKY_COUNT; ++l) {
			if (l == slot) continue;
			if (self->instanceTarget[l] == entity) {
				is_victim = true;
				break;
			}
		}
		if (is_victim) continue;

		if (entity->classID && IsVulnerableEnemy(entity, true) && IsEnemyOnScreen(entity)) {
			self->instanceTarget[slot] = entity;
			break;
		}

		if (!IsAttackableEntity(entity, 0)) continue;
		const uint32 index = entity->classID - AttackableClasses_startidx;
		const Vector2 old_pos = entity->position;
		if (AttackableClasses[index].adjustPos) AttackableClasses[index].adjustPos(entity);
		const bool32 visible = RSDK.CheckOnScreen(entity, NULL);
		entity->position = old_pos;
		if (!visible) continue;

		self->instanceTarget[slot] = entity;
		break;
	}
}