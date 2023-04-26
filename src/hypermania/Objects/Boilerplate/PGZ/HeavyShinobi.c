#include "HeavyShinobi.h"

ObjectHeavyShinobi* HeavyShinobi;
void (*HeavyShinobi_State_Idle)();
void (*HeavyShinobi_State_Slash)();
void (*HeavyShinobi_State_Jump)();
void (*HeavyShinobi_State_Glitched)();
void (*HeavyShinobi_State_Destroyed)();

bool32 HeavyShinobi_CheckVulnerable(Entity* self) {
	if (HeavyShinobi->invincibilityTimer) return false;
	return (
	    ((EntityHeavyShinobi*)self)->state == HeavyShinobi_State_Idle
	 || ((EntityHeavyShinobi*)self)->state == HeavyShinobi_State_Slash
	 || ((EntityHeavyShinobi*)self)->state == HeavyShinobi_State_Jump
	 || ((EntityHeavyShinobi*)self)->state == HeavyShinobi_State_Glitched
	);
}

Hitbox* HeavyShinobi_GetHitbox(Entity* self) { return &(HeavyShinobi->hitboxShinobi); }

void HeavyShinobi_OnHit(EntityPlayer* player, Entity* self) {
	if (((EntityHeavyShinobi*)self)->state == HeavyShinobi_State_Glitched) {
		if (HeavyShinobi->health) HeavyShinobi->health--;

		// HeavyShinobi_Hit() isn't a public function lol
		if (!HeavyShinobi->health) {
			SceneInfo->timeEnabled = false;
			Player_GiveScore(RSDK_GET_ENTITY(SLOT_PLAYER1, Player), 1000);
			RSDK.PlaySfx(HeavyShinobi->sfxExplosion, false, 255);
			((EntityHeavyShinobi*)self)->timer = 120;
			((EntityHeavyShinobi*)self)->state = HeavyShinobi_State_Destroyed;
		} else {
			RSDK.PlaySfx(HeavyShinobi->sfxHit, false, 255);
			((EntityHeavyShinobi*)self)->timer -= 60;
			HeavyShinobi->invincibilityTimer = 30;
		}
	} else {
		if (player->position.x >= self->position.x) {
			self->direction  = FLIP_X;
			self->velocity.x = -0x20000;
		} else {
			self->direction  = FLIP_NONE;
			self->velocity.x = 0x20000;
		}
		self->velocity.y = -0x40000;

		int32 angle        = RSDK.ATan2(player->position.x - self->position.x, player->position.y - self->position.y);
		((EntityHeavyShinobi*)self)->timer        = 180;
		((EntityHeavyShinobi*)self)->glitchTimer  = 0;

		RSDK.SetSpriteAnimation(HeavyShinobi->aniFrames, 15, &((EntityHeavyShinobi*)self)->mainAnimator, true, 0);
		RSDK.SetSpriteAnimation(HeavyShinobi->aniFrames, 5, &((EntityHeavyShinobi*)self)->fxAnimator, false, 0);
		RSDK.PlaySfx(HeavyShinobi->sfxParry, false, 255);
		((EntityHeavyShinobi*)self)->state = HeavyShinobi_State_Glitched;
	}
}

void HeavyShinobi_EnemyInfoHook(void) {
	Mod.Super(HeavyShinobi->classID, SUPER_STAGELOAD, NULL);
	ADD_ATTACKABLE_CLASS(HeavyShinobi->classID, HeavyShinobi_CheckVulnerable, HeavyShinobi_GetHitbox, HeavyShinobi_OnHit, NULL, ATKFLAG_ISBOSS);
}